#include "../include/irq.h"  
#include "../include/idt.h"
#include "../include/isr.h"
#include "../types.h"
#include "../../drivers/include/memory_io.h"

//void* interrupt_handerls[IRQS] = {0};

//pic1: responsible for IRQ 0-7
//pic2: responsible for IRQ 8-15
void irq_remap()
{   
    //The master pic(pic1) has command port 0x20 and data port 0x21, while the 
    //slave pic(pic2) has command port 0xA0 and data port 0xA1
    port_byte_out(0x20, 0x11);  //initialize pic1 
    port_byte_out(0x21, 32);    //set the base-vector for pic1 to 32 (0-7 -> 32-39).

    port_byte_out(0x21, 0x04);  //configures pic1 to know that pic2 is connected to irq2(of pic1). that way, when an interrupt occurs on pic2, it sends a signal to pic1 via irq2, then pic1 forwards the interrupt to the cpu
    port_byte_out(0x21, 0x01);  //set operating mode for pic1 (8086)

    
    port_byte_out(0xA0, 0x11);  //initialize pic2
    port_byte_out(0xA1, 40);    //set the base-vector for pic2 to 40 (8-15 -> 40-47)

    port_byte_out(0xA1, 0x02);  //configure pic2 to route interrupts through pic1
    port_byte_out(0xA1, 0x01);  //set operating mode for pic2 (8086)
}



void irq_install()
{
    //by default, the pic maps irq 0-7 to interrupt vector 8-15 and irq 8-15 to interrup vector 70-77 - which overlap with cpu exceptions
    //so to avoid conflicts, we remap the pic to use 32-47 instead.
    irq_remap();

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
    idt_set_gate(IRQ15, (u32bit)irq14, KERNEL_CS, 0, INTERRUPT_GATE);

}

void irq_handler(u32bit entry)
{
    int irq_number = entry - 32; //irqs in the idt start at offset 32.

    switch (irq_number)
    {
    case 0:
        //timer();
        break;
    
    case 1:
        //keyboard();
        break;

    default:
        break;
    }
    
    if (irq_number >= 8) {
        port_byte_out(0xA0, 0x20);  //send an EOI (end of interrupt) to the slave(pic2) pic if the irq number is bigger than 7.
    }
    port_byte_out(0x20, 0x20);  //send an EOI to pic1 anyway, cause to indicate that it can process further interrupts (cause pic2 is connected to pic1).
}