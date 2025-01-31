#ifndef IRQ_H
#define IRQ_H

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


#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 41
#define IRQ9 42
#define IRQ10 43
#define IRQ11 44
#define IRQ12 45
#define IRQ13 46
#define IRQ14 47



void irq_handler();
void irq_install();



#endif