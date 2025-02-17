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



#endif