// video memory starts at 0xb8000, but since we already wrote the pm message at that address, we'll start writing now at a little further address.
#define VIDEO_MEMORY_LOCATION 0xb8040

#define ROWS 25
#define COLUMNS 80

// define the byte for the default color scheme.
#define WHITE_ON_BLACK 0x0F 

// screen device i/o ports
#define CTRL_REG_SCREEN 0x3D4
#define DATA_REG_SCREEN 0x3D5
