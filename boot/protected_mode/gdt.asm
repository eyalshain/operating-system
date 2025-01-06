;GDT - global descriptor table
gdt_start:
    ;the null descriptor(8 bytes in size) is set to 0x0 and it handle cases where a segment
    ;register is forgot to be updated and . that way, the cpu treats it as invalid and 
    ;raise an exception, which can prevent invalid memory access and segmentation fault.
    null_descriptor:
        dd 0x0          ;4 bytes
        dd 0x0          ;4 bytes

    gdt_code:
        ;flag1:
        ; 1 = present. the segment is present in memory.
        ;00 = ring. ring 0 is the highest privilege.
        ; 1 = type. 1 for code/data. 0 for traps
        ;type flags:
        ; 1 = code. this is a code segment
        ; 0 = conforming. segments with lower privilege may not be able to call code in this segment (important for memory protection).
        ; 1 = readable. allow us to not only execute code, but to read constant defined in the code.
        ; 0 = accessed. (when the cpu set it to 1 when accessing the segment)

        ;flag2:
        ;1=Granularity. multiply out limit by 4k, so 0xfffff ==> 0xfffff000, allowing our segment to span 4gb
        ;1=32bit. since our segment will hold 32 bit code...if it was 16 bit it would be set to 0
        ;0=64bit code. unused on a 32bit processor
        ;0=userbit. for debugging... but we will not use it.
        ;1111=another 4 bit to allow the segment limit to be represented in a 20 bit format.
        ;
        
        dw 0xFFFF       ;limit(size)    bits(0-15)  
        dw 0            ;base address   bits(0-15)
        db 0            ;base address   bits(16-23)
        db 10011010b    ;flag1
        db 11001111b    ;flag2  , limit (bits 16-19)
        db 0x0          ;base address bits(24-31)

    gdt_data:
        ;same as the code segment, except the type flags in the the first flag(bits 0-3): from the right
        ;type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
        ;expand_down_bit - used for direction. 1-grows up. 0-grows down.

        dw 0xFFFF       ;Limit(size)    bits(0-15)
        dw 0x0          ;base address   bits(0-15)  
        db 0x0          ;base address   bits(16-23)
        db 10010010b   ;1st flags , type flags
        db 11001111b   ;2nd flags , Limit ( bits 16 -19)
        db 0x0          ;Base ( bits 24 -31)


gdt_end:  
    ;defining a label gdt_end so we can calculate the size of the gdt


;6-bytes structure: size(2-bytes) + starting_address(4-bytes)
gdt_descriptor:
    dw (gdt_end - gdt_start) - 1    ;GDT size. subtracting 1 for the extra
    dd gdt_start                    ;starting address of our GDT. (dd: double word - 4 bytes)  




; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT , which in our
; case is the DATA segment (0 x0 -> NULL ; 0x08 -> CODE ; 0 x10 -> DATA )
CODE_SEGMENT equ (gdt_code - gdt_start) 
DATA_SEGMENT equ (gdt_data - gdt_start)




;*each segment register is holding a selector - a 2-bytes value that points to an 
;entry in the GDT/LDT. that value contain: 
;1(index: tells the cpu which entry in GDT/LDT to look at)    bits(3-15)
;2(table indicator: GDT/LDT)                                  bits(2)
;3(privilege level: 00 - highest privilege)                   bits(0-1)  
