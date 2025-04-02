#ifndef IRQ_H
#define IRQ_H

#include "../types.h"


// Master PIC ports
#define PIC1_COMMAND 0x20  // Command port for Master PIC
#define PIC1_DATA    0x21  // Data port for Master PIC

// Slave PIC ports
#define PIC2_COMMAND 0xA0  // Command port for Slave PIC
#define PIC2_DATA    0xA1  // Data port for Slave PIC

// PIC commands
#define PIC_EOI      0x20  // End of interrupt command code




#define IRQS 16

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47


void irq_handler(u32bit entry);
void irq_install();
void irq_remap();
void enable_irq(u8bit offset);
void irq_unmask(int irq);

void disable_irq(u8bit offset);
void set_slave_IMR(u8bit imr);
void set_master_IMR(u8bit imr);
u8bit get_slave_IMR();
u8bit get_master_IMR();



#endif