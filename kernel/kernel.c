#include "../drivers/include/screen.h"

void kmain() {
    char *video_memory = (char*) 0xb802E;
    char *message = "  Hello kernel! ";

    while (*message)
    {
        *video_memory = *message;
        video_memory += 2;
        message += 1;
    }

    clear_screen();

}