[bits 16]

switch_to_pm:   
    cli                 ;disabling interrupts until we define the protected mode interrupts table,
                        ;so the cpu won't execute invalid - real mode interrupt.

    lgdt [gdt_descriptor]       ;load our global descriptor table to the GDTR.

    ;switching to protected mode - setting the first bit in the cr0 register.
    mov eax, cr0
    or  eax, 0x1
    mov cr0, eax

    
    jmp CODE_SEGMENT:init_pm    ;sets the cs to the selector in the GDT. this instruction is also important
                                ;to force the cpu to clear its cache of pre-fetched real mode instruction.
                                ;that way the cpu doesn't try to execute real mode decoded instruction, which will cause problems.

                                

[bits 32]                     

init_pm:

    mov ax, DATA_SEGMENT        ;updating all of segments register 
    mov ds, ax                  ;to the data selector we defined in the GDT.
    mov ss, ax
    mov es, ax 
    mov fs, ax  
    mov gs, ax

    ;init stack-pointer at 0x9000
    mov ebp, 0x90000            
    mov esp, ebp

    
