#include "../include/keyboard.h"
#include "../include/memory_io.h"
#include "../include/screen.h"

//the break code of a key = scancode of a key + 0x80. for example: shift-sc=0x2A. shift-release: 2A + 0x80 = 0xAA
#define RELEASE_CODE 0x80 //the release code is used for checking if a key was released. the byte 0xF0 IS SENT TO PORT 0X60 and then the scan code of the character is also sent to port 0x60

#define CTRL_SCANCODE 0x1D
#define ALT_SCANCODE 0x38
#define SHIFT_SCANCODE 0x2A
#define CAPSLOCK_SCANCODE 0x3A 

#define BACKSPACE_SCANCODE 0x0E
#define ENTER_SCANCODE 0x1C
#define TAB_SCANCODE 0x0F

#define MAX_SCANCODE 58


KeyEvent buffer[256] = {0}; //buffer to store all of the keys
u8bit key_count; // keys counter



//keyboard state - ctrl, shift, alt, ...
keyboard_state current_keyboard_state;
keyboard_state specific_keyboard_state;


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
        if (!update_keyboard_state(scancode)) {return; } //if the key is ctrl/shift/... exit the function and move to the next key
        
        int is_capital = is_capital_letter(scancode);

        char character = scancode_ascii[scancode][is_capital]; // gets the ascii code for the character using our scancode table.
        char str[2] = {character, '\0'};

        specific_keyboard_state = current_keyboard_state;
        KeyEvent current_key = {scancode, character, specific_keyboard_state};
        
        buffer[key_count] = current_key;
        key_count++;

        
        
        print(str); //printing the character

    }

}

int update_keyboard_state(u8bit scancode)
{

    switch(scancode)
    {
    case CTRL_SCANCODE:
        current_keyboard_state.is_ctrl_pressed = 1;
        return 1;
    
    case SHIFT_SCANCODE:
        current_keyboard_state.is_shift_pressed = 1;
        return 1;
    
    case ALT_SCANCODE:
        current_keyboard_state.is_alt_pressed = 1;
        return 1;
    
    case CAPSLOCK_SCANCODE:
        current_keyboard_state.is_capsLock_pressed = !current_keyboard_state.is_capsLock_pressed;
        return 1;
    
    default:
        break;
    }

    //to check if a key is released, we need to check if the scan code - 0x80 == to the target scan code.
    
    if (scancode - RELEASE_CODE == CTRL_SCANCODE)
    {
        current_keyboard_state.is_ctrl_pressed = 0;
        return 1;
    }

    if (scancode - RELEASE_CODE == SHIFT_SCANCODE)
    {
        current_keyboard_state.is_shift_pressed = 0;
        return 1;
    }

    if (scancode - RELEASE_CODE == ALT_SCANCODE)
    {
        current_keyboard_state.is_alt_pressed = 0;
        return 1;
    }
    

    return 0;
}


int is_capital_letter()
{
    return (current_keyboard_state.is_capsLock_pressed ^ current_keyboard_state.is_shift_pressed) != 0;
}