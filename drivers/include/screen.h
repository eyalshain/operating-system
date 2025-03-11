// video memory starts at 0xb8000, but since we already wrote the pm message at that address, we'll start writing now at a little further address.
//each row is 80 columns, and each cell is two byte, so to calclate the second row:
//0xb8000 + 80*2 = 0xb80A0
#define VIDEO_MEMORY_LOCATION 0xb80A0

//#define ROWS 25
#define ROWS 24
#define COLUMNS 80

// define the byte for the default color scheme.
#define WHITE_ON_BLACK 0x0F 

// screen device i/o ports
#define CTRL_REG_SCREEN 0x3D4
#define DATA_REG_SCREEN 0x3D5




void print (const char *message);
void print_at (const char *message, int row, int col);

int print_char (char character, int row, int col, int attribute_byte);
int get_cursor_offset ();
void set_cursor_offset (int offset);
void clear_screen ();
int handle_scrolling_at (int cursor_offset);
int handle_scrolling();
int back_space();
int tab();
int new_line();
char get_last_character();


int get_screen_offset (int col, int row);
int get_rows_offset (int offset);
int get_columns_offset (int offset);