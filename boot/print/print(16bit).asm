[bits 16]

;using int 10h with ah=0x0e to print a character to the string.
;this function gets a string in si and print it.
print_string16:
    pusha
    mov ah, 0x0E

print_loop:
    ;mov al, [si]
    ;inc si
    lodsb      ;perform the two instructions above
    cmp al, 0  ;checking if we reached the end of the string (\0)
    je done_print

    int 0x10    ;the 0x10 interrupt
    jmp print_loop

done_print:
    call new_line_16bit
    popa
    ret



new_line_16bit:
    mov ah, 0x0E
    mov al, 0x0A
    int 0x10

    mov al, 0x0D
    int 0x10

    ret