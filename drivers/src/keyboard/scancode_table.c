#include "../../include/keyboard.h"
#include "../../../libc/include/string.h"
#include "../../include/screen.h"

__attribute__((used)) char scancode_ascii[][2] = {
    {'?', '?'}, // 0 - No key
    {'?', '?'}, // 1 - ESC
    {'1', '!'}, // 2 - 1 / !
    {'2', '@'}, // 3 - 2 / @
    {'3', '#'}, // 4 - 3 / #
    {'4', '$'}, // 5 - 4 / $
    {'5', '%'}, // 6 - 5 / %
    {'6', '^'}, // 7 - 6 / ^
    {'7', '&'}, // 8 - 7 / &
    {'8', '*'}, // 9 - 8 / *
    {'9', '('}, // 10 - 9 / (
    {'0', ')'}, // 11 - 0 / )
    {'-', '_'}, // 12 - - / _
    {'=', '+'}, // 13 - = / +
    {'?', '?'}, // 14 - Backspace
    {'?', '?'}, // 15 - Tab
    {'q', 'Q'}, // 16 - q / Q
    {'w', 'W'}, // 17 - w / W
    {'e', 'E'}, // 18 - e / E
    {'r', 'R'}, // 19 - r / R
    {'t', 'T'}, // 20 - t / T
    {'y', 'Y'}, // 21 - y / Y
    {'u', 'U'}, // 22 - u / U
    {'i', 'I'}, // 23 - i / I
    {'o', 'O'}, // 24 - o / O
    {'p', 'P'}, // 25 - p / P
    {'[', '{'}, // 26 - [ / {
    {']', '}'}, // 27 - ] / }
    {'?', '?'}, // 28 - Enter
    {'?', '?'}, // 29 - Ctrl
    {'a', 'A'}, // 30 - a / A
    {'s', 'S'}, // 31 - s / S
    {'d', 'D'}, // 32 - d / D
    {'f', 'F'}, // 33 - f / F
    {'g', 'G'}, // 34 - g / G
    {'h', 'H'}, // 35 - h / H
    {'j', 'J'}, // 36 - j / J
    {'k', 'K'}, // 37 - k / K
    {'l', 'L'}, // 38 - l / L
    {';', ':'}, // 39 - ; / :
    {'\'', '"'}, // 40 - ' / "
    {'`', '~'}, // 41 - ` / ~
    {'?', '?'}, // 42 - LShift
    {'\\', '|'}, // 43 - \ / |
    {'z', 'Z'}, // 44 - z / Z
    {'x', 'X'}, // 45 - x / X
    {'c', 'C'}, // 46 - c / C
    {'v', 'V'}, // 47 - v / V
    {'b', 'B'}, // 48 - b / B
    {'n', 'N'}, // 49 - n / N
    {'m', 'M'}, // 50 - m / M
    {',', '<'}, // 51 - , / <
    {'.', '>'}, // 52 - . / >
    {'/', '?'}, // 53 - / / ?
    {'?', '?'}, // 54 - RShift
    {'?', '?'}, // 55 - PrtSc
    {'?', '?'}, // 56 - Alt
    {' ', ' '}, // 57 - Space
    {'?', '?'}  // 58 - Caps (Caps Lock)
};

void debug_scancode_table() {
    print("entered debug function from scancode.c file.");

    
    // char buf[2]; // Buffer to hold a single character + null terminator

    // for (int i = 0; i < 59; i++) {
    //     print("Scancode ");
    //     //print_hex(i); // Print scancode index
    //     print(": ");

    //     buf[0] = scancode_ascii[i][0]; // Store first character
    //     buf[1] = '\0'; // Null-terminate
    //     print(buf); // Print correctly

    //     print(", ");

    //     buf[0] = scancode_ascii[i][1]; // Store second character
    //     print(buf); // Print correctly

    //     print("\n\n");
    // }
}
