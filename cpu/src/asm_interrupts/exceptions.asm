global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

extern isr_common_stub
;[extern irq_common_stub]

;ISRS for exceptions

isr0:
    cli                         ;disabling interrupts while handling the current one
    add dword [esp], 3          ;since division usually takes 3 bytes, we need to adjust the EIP to not execute the same exception again.
    push dword 0                ;Division by Zero (Divide error)
    jmp isr_common_stub 

isr1:
    cli
    push dword 1                ;Debug Exception
    jmp isr_common_stub

isr2:
    cli
    push dword 2                ;Non-Maskable Interrupt (NMI)
    jmp isr_common_stub

isr3:
    cli
    push dword 3                ;Breakpoint Exception
    jmp isr_common_stub

isr4:
    cli
    push dword 4                ;Overflow Exception (INTO instruction)
    jmp isr_common_stub

isr5:
    cli
    push dword 5                ;Bound Range Exceeded Exception
    jmp isr_common_stub

isr6:
    cli
    push dword 6                ;Invalid Opcode Exception (CPU can't understand the instruction)
    jmp isr_common_stub
    
isr7:
    cli
    push dword 7                ;Device Not Available Exception (FPU not available)
    jmp isr_common_stub

isr8:
    cli
    push dword 8                ;Double Fault Exception
    jmp isr_common_stub

isr9:
    cli
    push dword 9                ;Coprocessor Segment Overrun (reserved by Intel)
    jmp isr_common_stub

isr10:
    cli
    push dword 10               ;Invalid Task State Segment (TSS) exception
    jmp isr_common_stub

isr11:
    cli
    push dword 11               ;Segment Not Present Exception
    jmp isr_common_stub

isr12:
    cli
    push dword 12               ;Stack Segment Fault Exception
    jmp isr_common_stub

isr13:
    cli
    
    push dword 13               ;General Protection Fault
    jmp isr_common_stub

isr14:
    cli
    push dword 14               ;Page Fault Exception (Memory access violation)
    jmp isr_common_stub

isr15:
    cli
    push dword 15               ;Reserved Exception
    jmp isr_common_stub

isr16:
    cli
    push dword 16               ;x87 FPU Floating-Point Error
    jmp isr_common_stub

isr17:
    cli
    push dword 17               ;Alignment Check Exception
    jmp isr_common_stub

isr18:
    cli
    push dword 18               ;Machine Check Exception (hardware fault)
    jmp isr_common_stub

isr19:
    cli
    push dword 19               ;Reserved Exception
    jmp isr_common_stub

isr20:
    cli
    push dword 20               ;Reserved Exception
    jmp isr_common_stub

isr21:
    cli
    push dword 21               ;Reserved Exception
    jmp isr_common_stub

isr22:
    cli
    push dword 22               ;Reserved Exception
    jmp isr_common_stub

isr23:
    cli
    push dword 23               ;Reserved Exception
    jmp isr_common_stub

isr24:
    cli                         
    push dword 24               ;Reserved Exception
    jmp isr_common_stub

isr25:
    cli
    push dword 25               ;Reserved Exception
    jmp isr_common_stub

isr26:
    cli
    push dword 26               ;Reserved Exception
    jmp isr_common_stub

isr27:
    cli
    push dword 27               ;Reserved Exception
    jmp isr_common_stub

isr28:
    cli
    push dword 28               ;Reserved Exception
    jmp isr_common_stub

isr29:
    cli
    push dword 29               ;Reserved Exception
    jmp isr_common_stub

isr30:
    cli
    push dword 30               ;Reserved Exception
    jmp isr_common_stub

isr31:
    cli
    push dword 31               ;Reserved Exception
    jmp isr_common_stub
