#include "../include/memory.h"

void memory_copy(char *source, char *dest, int bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        dest[i] = source[i];
    }
}

