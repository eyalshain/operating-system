#include "../drivers/include/screen.h"
#include "../cpu/include/isr.h"
#include "../libc/include/string.h"
#include "../cpu/include/irq.h"
#include "../cpu/include/idt.h"
#include "../drivers/include/keyboard.h"

void division_by_zero();
void welcome_msg();

void kmain() {
    char *video_memory = (char*) 0xb802E;
    char *message = "  Hello kernel!  ";

    while (*message)
    {
        *video_memory = *message;
        video_memory += 2;
        message += 1;
    }

    clear_screen();     //clear screen
    welcome_msg();      //print welcome message

    idt_init();
    isr_install();      //initialize ISRs
    irq_install();
    keyboard_init();

    


    //__asm__ __volatile__("sti");

    //division_by_zero();

    
    //print("wow! we are back bro!");
    //char *string = "wow! we are back bro!\n";
    //print(string);
    
    //handle_scrolling();
}

void division_by_zero()
{
    int num1 = 5;
    int num2 = 0;
    
    int result = num1 / num2;
    print("\ndamn! surprised u got here...\n");
}


void welcome_msg()
{
    print("  +------------------------------------------------------+\n");
    print("   |   [>         ] Booting... (10%)   |   .---.        | \n");  
    print("   |   [==>       ] Loading... (30%)   |   |o_o |       | \n");  
    print("   |   [====>     ] Almost...  (50%)   |   |:_/ |       | \n");  
    print("   |   [========> ] ...        (80%)   |  //   \\ \\      | \n");  
    print("   |   [=========>] Ready!     (100%)  |  (|     | )    | \n");  
    print("   |                                   |  /'\\_ _/`\\     | \n");  
    print("   |   Welcome to EyalOS!              |  \\__)=(__/     | \n"); 
    print("   +-----------------------------------------------------+\n\n");

}