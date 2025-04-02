#include "../include/idt.h"

__attribute__((aligned (0x10)))
idt_entry idt[IDT_ENTRIES];
idt_descriptor idt_ptr;

//function to set an entry in the idt(for a specific interrupt handler)
void idt_set_gate(int index, u32bit base, u16bit selector, u8bit reserved, u8bit flags)
{
    idt[index].offset_low = (base & 0xFFFF);    //takes the low 16 bits
    idt[index].offset_high = ((base >> 16) & 0xFFFF);   //takes the high 16 bits
    idt[index].selector = selector;
    idt[index].reserved = 0;
    idt[index].flags = flags;
}

void idt_init()
{
    idt_ptr.limit = (sizeof(idt_entry) * IDT_ENTRIES) - 1;  //size of the idt array.
    idt_ptr.base = (u32bit) &idt;   //address of the idt
    idt_load();
}

void idt_load()
{
    //__volatile__ - prevent the compiler from optimizing or ignoring this instruction if it think it's unnecessary
    __asm__ __volatile__("lidt (%0)": : "r"(&idt_ptr));
    //load idt (%0).    %0 = &idt_ptr. 
}