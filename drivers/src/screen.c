#include "../include/screen.h"

void print_char (char character, int rows, int columns, int attribute_byte)
{
    
    unsigned char *video_mem = (unsigned char*) VIDEO_MEMORY_LOCATION;

    // if attribute byte not specified, we'll use the default white_on_black
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    
}
