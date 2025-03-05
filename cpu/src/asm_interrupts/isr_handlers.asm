[extern isr_handler]
[extern irq_handler]

global isr_common_stub
global irq_common_stub

tmp dd 0
entry dd 0

isr_common_stub:
    mov [tmp], eax
    mov eax, [esp]
    mov [entry], eax 
    mov eax, [tmp]

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


    mov eax, [entry]
    push eax ;saving the interrupt vector, the entry in the idt array which the isr_handler gets as a parameter.

    call isr_handler    ;isr_handler - c function

    add esp, 4  ;cleaning the the isr_handler parameter - entry from the stack
    pop gs
    pop fs
    pop es
    pop ds
        
    
    popa

    add esp, 4  ;overriding the interrupt vector number that was pushed on the stack from the specific isr
    ;add dword [esp], 3

    ;jmp $
    sti ;enabling interrupts
    iret



irq_common_stub:
    mov [tmp], eax
    mov eax, [esp]
    mov [entry], eax 
    mov eax, [tmp]
    
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

    mov eax, [entry]
    push eax ;saving the interrupt vector, the entry in the idt array which the isr_handler gets as a parameter.

    call irq_handler    ;isr_handler - c function

    add esp, 4
    pop gs
    pop fs
    pop es
    pop ds
    
    popa

    add esp, 4

    ;jmp $
    sti ;enabling interrupts
    iret