#include "../include/irq.h"  
#include "../include/idt.h"
#include "../include/isr.h"
#include "../types.h"

void irq_install()
{
    idt_set_gate(IRQ0, (u32bit)irq0, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ1, (u32bit)irq1, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ2, (u32bit)irq2, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ3, (u32bit)irq3, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ4, (u32bit)irq4, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ5, (u32bit)irq5, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ6, (u32bit)irq6, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ7, (u32bit)irq7, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ8, (u32bit)irq8, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ9, (u32bit)irq9, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ10, (u32bit)irq10, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ11, (u32bit)irq11, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ12, (u32bit)irq12, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ13, (u32bit)irq13, KERNEL_CS, 0, INTERRUPT_GATE);
    idt_set_gate(IRQ14, (u32bit)irq14, KERNEL_CS, 0, INTERRUPT_GATE);

}
