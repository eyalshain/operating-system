#include "../include/irq.h"  
#include "../include/idt.h"
#include "../include/isr.h"
#include "../types.h"
#include "../../drivers/include/memory_io.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../libc/include/string.h"

//void* interrupt_handerls[IRQS] = {0};

//pic1: responsible for IRQ 0-7
//pic2: responsible for IRQ 8-15
void irq_remap()
{   
    //The master pic(pic1) has command port 0x20 and data port 0x21, while the 
    //slave pic(pic2) has command port 0xA0 and data port 0xA1
    port_byte_out(PIC1_COMMAND, 0x11);  //initialize pic1 
    port_byte_out(PIC1_DATA, 32);    //set the base-vector for pic1 to 32 (0-7 -> 32-39).

    port_byte_out(PIC1_DATA, 0x04);  //configures pic1 to know that pic2 is connected to irq2(of pic1). that way, when an interrupt occurs on pic2, it sends a signal to pic1 via irq2, then pic1 forwards the interrupt to the cpu
    port_byte_out(PIC1_DATA, 0x01);  //set operating mode for pic1 (8086)

    
    port_byte_out(PIC2_COMMAND, 0x11);  //initialize pic2
    port_byte_out(PIC2_DATA, 40);    //set the base-vector for pic2 to 40 (8-15 -> 40-47)

    port_byte_out(PIC2_DATA, 0x02);  //configure pic2 to route interrupts through pic1
    port_byte_out(PIC2_DATA, 0x01);  //set operating mode for pic2 (8086)


    port_byte_out(PIC1_DATA, 0xFF); // Mask all IRQs on master PIC
    port_byte_out(PIC2_DATA, 0xFF); // Mask all IRQs on slave PIC
}



void irq_install()
{
    //by default, the pic maps irq 0-7 to interrupt vector 8-15 and irq 8-15 to interrup vector 70-77 - which overlap with cpu exceptions
    //so to avoid conflicts, we remap the pic to use 32-47 instead.
    irq_remap();
    enable_irq(1);
    

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
    __asm__ __volatile__("sti");

    //print("\ninitilized IRQs successfully\n");
}

void irq_handler(u32bit entry)
{
    //print("\nsuccessfully Entered into irq_handler\n");
    int irq_number = entry - 32; //irqs in the idt start at offset 32.

    char *irq_str;
    itoa(irq_number, irq_str);
    
    
    // print(irq_str);
    // //print("\n");
    
    

    switch (irq_number)
    {
    case 0:
        //timer();
        break;
    
    case 1:
        //handle_scrolling();
        keyboard_handler();
        break;

    default:
        break;
    }
    
    if (irq_number >= 8) {
        port_byte_out(PIC2_COMMAND, PIC_EOI);  //send an EOI (end of interrupt) to the slave(pic2) pic if the irq number is bigger than 7.
    }
    port_byte_out(PIC1_COMMAND, PIC_EOI);  //send an EOI to pic1 anyway, cause to indicate that it can process further interrupts (cause pic2 is connected to pic1).
}


u8bit get_master_IMR() {
    return port_byte_in(PIC1_DATA); // read the master PIC IMR
}

u8bit get_slave_IMR() {
    return port_byte_in(PIC2_DATA); // read the slave PIC IMR
}

void set_master_IMR(u8bit imr) {
    port_byte_out(PIC1_DATA, imr);
}

void set_slave_IMR(u8bit imr) {
    port_byte_out(PIC2_DATA, imr);
}

void enable_irq(u8bit offset) {
    u8bit imr = (offset < 8) ? get_master_IMR() : get_slave_IMR(); // get slave / master IMR by the given offset.
    imr &= ~(1 << offset);  // enable irq bit by set the bit to 1 by using 'not' & 'and' bitwise
    (offset < 8) ? set_master_IMR(imr) : set_slave_IMR(imr); // set IMR
}

void disable_irq(u8bit offset) {
    u8bit imr = (offset < 8) ? get_master_IMR() : get_slave_IMR(); // get slave / master IMR by the given offset.
    imr |= (1 << offset);  // disable irq bit by set the bit to 0 using 'or' bitwise
    (offset < 8) ? set_master_IMR(imr) : set_slave_IMR(imr); // set IMR
}
