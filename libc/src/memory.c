#include "../include/memory.h"

void memory_copy(char *source, char *dest, int bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        dest[i] = source[i];
    }
}

void memset(void *src, char value, int bytes)
{
    unsigned char *src_ptr = (unsigned char*) src;
    for (int i = 0; i < bytes; i++)
    {
        src_ptr[i] = value;
    }
}