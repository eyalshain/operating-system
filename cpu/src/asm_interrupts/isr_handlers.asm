[extern isr_handler]
[extern irq_handler]

global isr_common_stub

tmp dd 0

isr_common_stub:
    mov eax, [esp]
    mov [tmp], eax 
    pusha

    push ds
    push es
    push fs
    push gs 

    mov ax, 0x10    ;data segments selector = 0x10. defined in the GDT.
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 

    mov eax, [tmp]
    push eax ;saving the interrupt vector, the entry in the idt array which the isr_handler gets as a parameter.

    call isr_handler    ;isr_handler - c function

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    
    popa

    jmp $
    ;sti ;enabling interrupts
    ;ret


	