#include "../include/keyboard.h"
#include "../include/memory_io.h"
#include "../include/screen.h"
#include "../../libc/include/string.h"

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


KeyEvent buffer[KEYBOARD_BUFFER_SIZE] = {0}; //buffer to store all of the keys
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
    // print("before handle_scrolling.");
    handle_scrolling();

    //reading the character's scancode form port 0x60
    u8bit scancode = port_byte_in(0x60);

    // char *new;
    // itoa(scancode, new);
    // print(new);
    // print(" ");

    if (update_keyboard_state(scancode) == 1) {return; } //if the key is ctrl/shift/... exit the function and move to the next key

    //if the scancode is bigger than the max scancode (+ 0x80, for key releases.)
    if (scancode > MAX_SCANCODE) return;

    //handle scancodes.
    if (scancode == ENTER_SCANCODE) { new_line(); }
    else if (scancode == BACKSPACE_SCANCODE) { handle_backspace(); }
    else if (scancode == TAB_SCANCODE) { tab(); }

    else {
        //handle regular keys
        int is_capital = is_capital_letter(scancode);

        char character = scancode_ascii[scancode][is_capital]; // gets the ascii code for the character using our scancode table.
        char str[2] = {character, '\0'};

        specific_keyboard_state = current_keyboard_state;
        KeyEvent current_key = {scancode, character, specific_keyboard_state};
        
        buffer[key_count] = current_key;
        key_count = (key_count + 1) % KEYBOARD_BUFFER_SIZE; //increase the keycounter by 1, but make sure that if it exceed the limit - reset the counter.

        
        print(str); //printing the character
        // char *new_str;
        // itoa(current_keyboard_state.is_shift_pressed, new_str);

        // print(new_str);
        // print(" ");
        

    }

}

int update_keyboard_state(u8bit scancode)
{
    // char *new_str;
    // itoa(scancode, new_str);

    // print(new_str);
    // print(" ");
    
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

    // to check if a key is released, we need to check if the scan code - 0x80 == to the target scan code.
    // u8bit key_code = scancode - RELEASE_CODE;
    

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

void handle_backspace()
{   

    int is_ctrl = current_keyboard_state.is_ctrl_pressed;

    switch(is_ctrl) {

    case 1:  //ctrl is pressed, delete the entire word, and if it's a space (empty character ' '), delete until the end of the word
        if (get_last_character() != ' ')
        {
            while (get_last_character() != ' ')
            {
                back_space();
            }
        }
        else
        {
            while (get_last_character() == ' ')
            {
                back_space();
            }
        }

    case 0:  //backspace once.
        back_space();
    }

}


void clean_buffer()
{
    
}