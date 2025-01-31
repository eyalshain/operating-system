#include "../include/isr.h"
#include "../include/idt.h"
#include "../types.h"
#include "../../drivers/include/screen.h"

//char* exceptions_names[32];

char* exceptions_names[32] = {
    "division by zero",
    "debug exception",
    "non-maskable interrupt",
    "breakpoint exception",
    "overflow exception",
    "bound range exceeded",
    "invalid opcode",
    "device not available",
    "double fault",
    "coprocessor segment overrun",
    "invalid TSS",
    "segment not present",
    "stack fault",
    "general protection fault",
    "page fault",
    "reserved 1",
    "x87 floating point exception",
    "alignment check",
    "machine check",
    "SIMD floating point exception",
    "virtualization exception",
    "control protection exception",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved ",
    "reserved "
};


void isr_install()
{
    //setting each entry in the idt its index, code selector(0x10), reserved(0) and interrupt gate(0x8E)
    idt_set_gate(0, (u32bit)isr0, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(1, (u32bit)isr1, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(2, (u32bit)isr2, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(3, (u32bit)isr3, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(4, (u32bit)isr4, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(5, (u32bit)isr5, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(6, (u32bit)isr6, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(7, (u32bit)isr7, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(8, (u32bit)isr8, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(9, (u32bit)isr9, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(10, (u32bit)isr10, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(11, (u32bit)isr11, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(12, (u32bit)isr12, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(13, (u32bit)isr13, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(14, (u32bit)isr14, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(15, (u32bit)isr15, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(16, (u32bit)isr16, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(17, (u32bit)isr17, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(18, (u32bit)isr18, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(19, (u32bit)isr19, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(20, (u32bit)isr20, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(21, (u32bit)isr21, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(22, (u32bit)isr22, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(23, (u32bit)isr23, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(24, (u32bit)isr24, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(25, (u32bit)isr25, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(26, (u32bit)isr26, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(27, (u32bit)isr27, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(28, (u32bit)isr28, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(29, (u32bit)isr29, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(30, (u32bit)isr30, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(31, (u32bit)isr31, KERNEL_CS, 0, INTERRUPT_GATE);

    //after setting all of the exceptions entries, initializing the idt limit and address, and loading the idtr 
    //register with the idt_desc, which tells the cpu where is the idt and its size.
    idt_init();
}



void isr_handler(u32bit entry) {
    char *name = exceptions_names[entry];

    print("\nEncountered a exception: \n");
    print(name);
    print("\n\0");
    
}