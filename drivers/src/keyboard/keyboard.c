#include "../../include/keyboard.h"
#include "../../include/memory_io.h"
#include "../../include/screen.h"
#include "../../../libc/include/string.h"
#include "../../../libc/include/memory.h"

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
char keys_buf[KEYBOARD_BUFFER_SIZE] = {0};
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

    if (update_keyboard_state(scancode) == 1) {return; } //if the key is ctrl/shift/... exit the function and move to the next key

    //if the scancode is bigger than the max scancode (+ 0x80, for key releases.)
    if (scancode > MAX_SCANCODE) return;

    //handle scancodes.
    if (scancode == ENTER_SCANCODE) { new_line(); }
    else if (scancode == BACKSPACE_SCANCODE) { handle_backspace(); }
    else if (scancode == TAB_SCANCODE) { tab(); }

    else {
        //handle regular keys
        print_key(scancode);
    }

}

//this function gets a scancode, update the global KeyEvent buffer and print the character.
void print_key(u8bit scancode)
{
    
    //checks if the letter is supposed to be uppercase.
    int is_capital = is_capital_letter();

    // gets the ascii code for the character using our scancode table.
    char character = scancode_ascii[scancode][is_capital]; 
    keys_buf[key_count] = character;
    char str[2] = {character, '\0'};

    //creating a 'KeyEvent' that will represent the current keyboard state
    specific_keyboard_state = current_keyboard_state;
    KeyEvent current_key = {scancode, character, specific_keyboard_state};
    
    //updating the buffer in the current.
    buffer[key_count] = current_key;
    key_count = (key_count + 1) % KEYBOARD_BUFFER_SIZE; //increase the keycounter by 1, but make sure that if it exceed the limit - reset the counter.

    print("\nyoo");
    print(str);
    
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


void reset_keyboard_buffer()
{
    memset(buffer, 0, KEYBOARD_BUFFER_SIZE);
    key_count = 0;
}


KeyEvent get_last_event()
{
    
    if (key_count == 0)
    {
        return buffer[KEYBOARD_BUFFER_SIZE - 1];
    }

    return buffer[key_count-1];
}

char key_to_ascii(KeyEvent key)
{
    u8bit scancode = key.scancode;
    int is_capital = (key.state.is_capsLock_pressed ^ key.state.is_shift_pressed) != 0;

    char character = scancode_ascii[scancode][is_capital];

    return character;
}

//this function read a command, puts it in buf and return the counter - how many letter have readed
u32bit ReadCommand(char *buf)
{
    //reset_keyboard_buffer();

    char character;
    u32bit counter = 0;

    // wait until the user press enter
    while (get_last_event().ascii_code != '\n') {}

    while (counter < KEYBOARD_BUFFER_SIZE && get_last_event().ascii_code != '\n')
    {
        buf[counter] = buffer[counter].ascii_code;
        counter++;
    }


    return counter;
}