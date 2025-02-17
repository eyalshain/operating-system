#ifndef MEMORY_IO_H
#define MEMORY_IO_H

unsigned char port_byte_in (unsigned short port);
unsigned char port_word_in (unsigned short port);

void port_byte_out (unsigned short port, unsigned char data);
void port_word_out (unsigned short port, unsigned short data);

#endif