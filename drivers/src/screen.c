#include "../include/screen.h"
#include "../include/memory_io.h"
#include "../../libc/include/memory.h"


//this function prints a message to the screen at a given row and column using video memory.
void print_at (const char *message, int row, int col)
{
    int offset;

    //if row and col are valid, calculate the offset, if not, write at the cursor position.
    if (row >= 0 && col >= 0) {
        offset = get_screen_offset(col, row);
    }
    else {
        offset = get_cursor_offset();
        row = get_rows_offset(offset);
        col = get_columns_offset(offset);
    }

    int i = 0;
    while (message[i] != '\0')
    {
        //using the print_char function to write to video memory.
        offset = print_char(message[i], row, col, WHITE_ON_BLACK);
        row = get_rows_offset(offset);
        col = get_columns_offset(offset);
        i++;
    }

}

//this function write to the screen at the cursor position.
void print (const char *message)
{
    print_at(message, -1, -1);
}


/*
******************************************
*          HELPER FUNCTIONS!!            *  
******************************************
*/

int print_char (char character, int row, int col, int attribute_byte)
{
    
    unsigned char *video_mem = (unsigned char*) VIDEO_MEMORY_LOCATION;

    // if attribute byte not specified, we'll use the default white_on_black
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;

    // if row and col are valid, use them to get the offset. if not, set the offset to the cursor position
    if (row >= 0 && col >= 0){
        offset = get_screen_offset(col, row);
    }
    else {
        offset = get_cursor_offset();
    }

    // if the character is a newline-char, update the offset to the start of the next line.
    if (character == '\n') {
        row = get_rows_offset(offset);
        col = 0;
        offset = get_screen_offset(col, row + 1);
    }
    else {
        //else, write the character and its attribute to video memory and add 2 to the offset.
        video_mem[offset] = character;
        video_mem[offset + 1] = attribute_byte;
        offset += 2;
    }

    set_cursor_offset(offset);
    
    return offset;
}


int handle_scrolling() {    //uses the cursor position automatically 
    handle_scrolling_at(-1);
}

//if the cursor is out of video memory, scroll one line and  delete the top line.
int handle_scrolling_at (int cursor_offset)
{

    int max_bytes = 2 * ROWS * COLUMNS;

    if (cursor_offset < 0)  // use this in another function that doesn't get any parameter and automatically uses the cursor offset.
    {
        cursor_offset = get_cursor_offset();
    }

    //if the cursor is still in the screen(didn't exceed the max bytes limit) return the cursor_offset unmodified
    if (cursor_offset < max_bytes) {
        return cursor_offset;
    }

    //shift each row by one towards the top by using the memcpy function from libc.
    for (int i = 1; i < ROWS; i++)
    {
        memory_copy(
            (char *)(VIDEO_MEMORY_LOCATION + get_screen_offset(0, i)),
            (char *)(VIDEO_MEMORY_LOCATION + get_screen_offset(0, i - 1)),
            COLUMNS * 2
        );
    }
    
    //clear the last row 
    char *last_row = VIDEO_MEMORY_LOCATION + (char *)get_screen_offset(0, ROWS - 1);
    for (int i = 0; i < COLUMNS * 2; i++)
    {
        last_row[i*2] = 0; //ascii code 0 for each character
        last_row[i*2 + 1] = 0x07; //setting the color to 0x07-light gray on black
    }

    //cursor position - last row, first column.
    cursor_offset = get_screen_offset(0, ROWS - 1);

    //setting the cursor for the correct offset.
    set_cursor_offset(cursor_offset);
    
    
    //returning the cursor offset.
    return cursor_offset;
}

char get_last_character()
{
    int current_offset = get_cursor_offset();
    int key_offset = current_offset - 2;

    char character = ((char*)VIDEO_MEMORY_LOCATION)[key_offset];
    return character;
}

void clear_screen ()
{
    int screen_size = ROWS * COLUMNS; //calculate the max number of cells (each cell is 2 bytes.)
    char *value = (char *) VIDEO_MEMORY_LOCATION;

    //iterating through the screen and setting the the char of each cell to ' ', and the color
    //to white on black.
    for (int i = 0; i < screen_size; i++)
    {
        value[i * 2] = ' ';
        value[(i * 2) + 1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_screen_offset(0, 0));
}

int back_space()
{
    int offset = get_cursor_offset(); //current cursor offset
    offset -= 2; //since each cell in video memory in 2 bytes, we gonna subtract form the offset 2, because we deleting the current char.

    set_cursor_offset(offset);  //setting the offset

    char *current_cell = (char *)VIDEO_MEMORY_LOCATION;

    current_cell[offset] = ' '; //deleting the current cell, by placing ' ' char and a white on black.
    current_cell[offset + 1] = WHITE_ON_BLACK;

    return offset;
}

//move the cursor by 4 spaces.
int tab()
{
    //getting the current cursor offset.
    int offset = get_cursor_offset();
    int cell = 2; //one cell = 2 bytes

    offset += cell * 4;

    set_cursor_offset(offset);
    return offset;
}

//moves the cursor to the next line.
int new_line()
{
    // getting the current cursor offset
    int offset = get_cursor_offset();

    int row = get_rows_offset(offset);
    int column = 0;

    row++; //to get to the next line, we want to column to be 0 and the row to be -> current row + 1

    //calculate the new offset by the row and column we just calculated.
    int new_offset = get_screen_offset(column, row); 

    set_cursor_offset(new_offset);  //setting the current offset to be the new offset.

    return offset;
}


int get_cursor_offset ()
{
    //sending the value 14 to port 0x3D4 (vga control register).
    //this tells the vga controller to prepare access for the high byte of the cursor position.
    port_byte_out(CTRL_REG_SCREEN, 14); 
    int offset = port_byte_in(DATA_REG_SCREEN) << 8;    //reading the high byte, and shifting it 8 bits to the left, to make room for another byte.
    port_byte_out(CTRL_REG_SCREEN, 15);     //same for the low byte.
    offset += port_byte_in(DATA_REG_SCREEN);

    
    //multiplying the offset by 2, since each character cell is 2 bytes in the vga text mode.
    offset *= 2;    
    return offset;
}

void set_cursor_offset (int offset)
{
    offset /= 2;

    //by shifting 8 bits to the right, it takes the high byte of the offset, place it at the low byte position.
    //doing: & 0xFF will make sure that only the "low" byte (which is the high byte) will be written.
    port_byte_out(CTRL_REG_SCREEN, 14); //prepare access for the high byte of the cursor position
    port_byte_out(DATA_REG_SCREEN, (unsigned char) (offset >> 8) & 0xFF); //writing the high byte of the offset to the data port.
    port_byte_out(CTRL_REG_SCREEN, 15); //same for low byte.
    port_byte_out(DATA_REG_SCREEN, (unsigned char) (offset) & 0xFF);
}


//calculate where in video memory(0xb8000) data should be written to (multiplied by 2, because each cell is 2 bytes).
int get_screen_offset (int col, int row)
{
    return 2 * (row * COLUMNS + col);
}
//calculating the current row by a given offset
int get_rows_offset (int offset)
{
    return offset / (2 * COLUMNS);
}

//calculating the current columns by a given offset by subtracting the starting byte of the row from the current offset.
int get_columns_offset (int offset)
{
    return (offset - get_screen_offset(0, get_rows_offset(offset))) / 2; 
}