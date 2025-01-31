#include "../drivers/include/screen.h"
#include "../cpu/include/isr.h"

void division_by_zero();

void kmain() {
     char *video_memory = (char*) 0xb802E;
    //char *video_memory = (char*) 0xb8100;
    char *message = "  Hello kernel!  ";

    while (*message)
    {
        *video_memory = *message;
        video_memory += 2;
        message += 1;
    }

    //clear_screen();
    print_at("HI, Eyal :) what's up? ", 0, 0);
    //print("this is so cool!!!");

    isr_install();
    division_by_zero();
    //print("Hi");


    /*
    clear_screen();
    //print_at("Hello, eyal!", 0, 0);

    for (int i = 0; i < 23; i++)
    {
        print_at("sup bro?", i, 0);
    }
    for (int i = 0; i < COLUMNS; i++)
    {
        print_at("a", 23, i);   //print a bunch of 'a' at the last row
    }

    handle_scrolling(get_cursor_offset());
    print("Hi, bro:)");
    */
}

void division_by_zero()
{
    int num1 = 5;
    int num2 = 0;
    
    int result = num1 / num2;
}