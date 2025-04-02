#include "../include/memory_io.h"

//ports are addresses that allows the cpu to interact with hardware devices. let's say we wrote a keyboard driver,
//that always keep checking port(address) 0x60 for new data - then it translate the scan code into a press(for example, scan code  A: 0x1E)
//
unsigned char port_byte_in (unsigned short port)
{
    //using inline assembly - dx is loaded with the port, al is assign the result value (the data from the port)
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

unsigned char port_word_in (unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}



void port_byte_out (unsigned short port, unsigned char data)
{
    //loading al with data, and writing it to the specified port.
    __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

void port_word_out (unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx": : "a" (data), "d" (port));
}