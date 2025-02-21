#include "../include/keyboard.h"
#include "../include/memory_io.h"
#include "../include/screen.h"


#define BACKSPACE_SCANCODE 0x0E
#define ENTER_SCANCODE 0x1C
#define TAB_SCANCODE 0x0F

#define MAX_SCANCODE 58



KeyEvent buffer[256] = {0}; //buffer to store all of the keys
u8bit key_count; // keys counter

char scancode_ascii[][2];   //scancode table. using this to convert scancodes into ascii characters.

//keyboard state - ctrl, shift, alt, ...
keyboard_state current_keyboard_state;


void keyboard_init()
{
    key_count = 0;

    current_keyboard_state.is_alt_pressed = 0;
    current_keyboard_state.is_capsLock_pressed = 0;
    current_keyboard_state.is_ctrl_pressed = 0;
    current_keyboard_state.is_shift_pressed = 0;
}


void keyboard_handler()
{
    //reading the character's scancode form port 0x60
    u8bit scancode = port_byte_in(0x60);

    if (scancode > MAX_SCANCODE) return;

    //handle scancodes.
    if (scancode == ENTER_SCANCODE) { new_line(); }
    else if (scancode == BACKSPACE_SCANCODE) { back_space(); }
    else if (scancode == TAB_SCANCODE) { tab(); }

    else {
        //handle regular keys
        char character = scancode_ascii[(int)scancode]; // gets the ascii code for the character using our scancode table.
        print(character); //printing the character

    }

}
