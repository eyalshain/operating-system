ENTRY(_start)

SECTIONS
{
    . = 0x1000;

    /* Combined text and rodata */
    .text : {
        *(.text)
        *(.rodata*)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(COMMON)
        *(.bss)
    }
}