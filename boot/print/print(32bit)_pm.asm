;since we are in protected mode now, we cannot use the bios interrupt, because they
;only work for 16 bit mode.
[bits 32]

;prints a null-terminated string pointed to by ebx
print_string32:
    pusha
    mov edx, VIDEO_MEMORY

print_loop32:
    ;each character cell of the screen is represented by two bytes in memory: the 
    ;first byte is the ASCII code of the character, the second byte encodes the characters
    ;attributes, such as the foreground and background color.
    
    mov al, byte [ebx]         ;the ascii code for the actual character
    mov ah, WHITE_ON_BLACK     ;foreground and background color

    cmp al, 0                  ;if we reach the end of the string(null-terminator) 
    je done_print32            ;then done printing 

    mov [edx], ax              ;writing the 2 bytes(ascii and color) to video memory 

    add ebx, 1                 ;increment ebx to move to the next character
    add edx, 2                 ;move to the next cell in video memory

    jmp print_loop32           ;loop until we reach the end of the string. 


done_print32:   
    popa
    ret







VIDEO_MEMORY equ 0xb8000    ;VGA text mode start at 0xb8000
WHITE_ON_BLACK equ 0x0F     ;0xF=white. 0x0=black.


