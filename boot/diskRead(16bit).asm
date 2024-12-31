[bits 16]

;input: ax=lba value. cl=sectors to read. dl=drive_number
;output:
; cx [bits 0-5]: sector number
; cx [bits 6-15]: cylinder
; dh: head

lba_to_chs:
    push ax
    push dx

    xor dx, dx

    div word [bdb_sectors_per_track]    ; ax / sectors_per_track:
                                        ; (lba % sectors_per_track) + 1 = sector
    inc dx                              ; reminder stores in dx, so all we need to do in increase dx by one and get the sector
    mov cx, dx
    xor dx, dx  ; moving dx into cx, so we can use dx again.

    ; head:     (LBA/sectors_per_track) % number of heads
    ; cyilnder: (LBA/sectors_per_track) / number of heads
    ;           (LBA/sectors_per_track) is already store in ax, so lets do another division:

    div word [bdb_heads]     ; ((LBA/sectors_per_track) / number of heads) -> ax
    mov dh, dl      ; head number in dh for interrupt 13
    mov ch, al      ; al containing the cyilnder, now we gonna move it to ch
    shl ah, 6
    or cl, ah       ; cyilnder

    pop ax
    mov dl, al
    pop ax
    
    ret


;using bios interrupt(int 13h) to read from the disk. the interrupt require us to have
;the registers in chs format, so we calling the lba_to_chs to convert the lba to chs
;(since chs is much more understandable to use.)
disk_read:
    push ax
    push bx
    push cx
    push dx
    push di

    mov [sectors_to_read], cl   

    call lba_to_chs

    mov ah, 0x2
    mov al, [sectors_to_read]
    mov di, 3

retry:
    ;CF = 0 if successful
    ;CF = 1 if error

    stc     ; set the carry
    int 13h
    jnc done_read

    call disk_reset     
    
    dec di 
    test di, di
    jnz retry

fail_disk_read:
    mov si, read_failure 
    call print
    hlt
    jmp halt


disk_reset:
    pusha
    mov ah, 0   ; interrupt 13, ah = 0. for resting the disk drivers
    stc
    int 13h
    jc fail_disk_read
    popa
    ret

done_read:  
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    
    ret



sectors_to_read db 0
read_failure db 'ERROR: failed to read from disk'