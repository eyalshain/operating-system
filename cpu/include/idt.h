#ifndef IDT_H
#define IDT_H

#include "types.h"

#define IDT_ENTRIES 256
#define KERNEL_CS 0x08          //code segment, index 1 in the GDT(value 0x08)
#define INTERRUPT_GATE 0x8E     //when handling hardware interrupt, we want to use the interrupt gate (0x8E - 10001110) which disables interrupt, runs the interrupt handler in kernel mode(ring 0) and the cpu pushes EFLAGS, CS, and EIP onto the stack before jumping to the handler to save its current state.


//idt entry
typedef struct __attribute__((packed)) {        //__attribute__((packed)) ensure the idt entry is exactly 8 bytes - what the cpu expect. otherwise, the compiler might add padding(extra bytes).
    u16bit offset_low;      //lower 16 bit of the handler function address 
    u16bit selector;        //GDT selector.
    u8bit reserved;         //always set to 0.
    u8bit flags;            
    u16bit offset_high;     //higher 16 bit of the handler function address.
} idt_entry;


//idt_descriptor - tells the cpu where the idt is and its size.
typedef struct __attribute__((packed)) {
    u16bit limit;   //size of the idt
    u32bit base;    //base address of the idt
} idtr_t; 

//defining the idt array and the idt pointer
__attribute__((aligned (0x10)))
idt_entry idt[IDT_ENTRIES];
idtr_t idt_ptr;


void idt_set_gate(int index, u32bit base, u16bit selector, u8bit reserved, u8bit flags);
void idt_load();
void idt_init();

#endif

