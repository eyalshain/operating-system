#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../../cpu/types.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_BUFFER_SIZE 256



typedef struct {
    u8bit is_ctrl_pressed;
    u8bit is_shift_pressed;
    u8bit is_capsLock_pressed;
    u8bit is_alt_pressed;
} keyboard_state;

typedef struct {
    u8bit scancode;
    u8bit ascii_code;
    keyboard_state state;
} KeyEvent;


void keyboard_init();
void keyboard_handler();
int update_keyboard_state(u8bit scancode);
int is_capital_letter();
void clean_buffer();
void handle_backspace();


//scancode table: https://www.millisecond.com/support/docs/current/html/language/scancodes.htm
//we'll use this array to convert a scancode to an ascii represntation.
extern char scancode_ascii[][2];


#endif