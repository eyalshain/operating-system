C_SOURCE = $(wildcard kernel/*.c  drivers/src/*.c libc/src/*.c cpu/src/*.c)
HEADERS = $(wildcard kernel/*.h drivers/include/*.h libc/include/*.h cpu/include/*.h cpu/types.h)
ASM_SOURCES = $(wildcard cpu/src/asm_interrupts/*.asm)

CROSS_COMPILER = /usr/local/cross/bin/i386-elf
OBJ = ${C_SOURCE:.c=.o} ${ASM_SOURCES:.asm=.o}

CC = $(CROSS_COMPILER)-gcc
LD = $(CROSS_COMPILER)-ld
GDB = $(CROSS_COMPILER)-gdb

# Debug build flags
DEBUG_CFLAGS = -g -O0 -ffreestanding -m32 -fno-pic -Wall -Wextra

# Release build flags
RELEASE_CFLAGS = -g -ffreestanding -m32 -fno-pic

# Default to release build
CFLAGS = $(RELEASE_CFLAGS)

run: all
	qemu-system-i386 -fda os_image.bin

all: os_image.bin

# Building the OS image file
os_image.bin: boot/boot_sector.bin kernel.bin
	cat $^ > $@

# Linking the kernel
kernel.bin: boot/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386  -T linker.ld -o $@  $^ --oformat binary

# used for debugging
kernel.elf: boot/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ 

# Rule to build the boot sector in the boot folder
boot/boot_sector.bin: boot/boot_sector.asm
	nasm $< -f bin -o $@

# Rule to build the kernel entry in the boot folder
boot/kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf32 -o $@

# Rule to compile C files
%.o : %.c ${HEADERS}
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to assemble ASM files
%.o : %.asm
	nasm $< -f elf32 -o $@

# Clean build artifacts
clean:
	rm -fr build/*.bin build/*.o *.bin *.o os_image
	rm -fr kernel/*.o boot/*.bin boot/*.o drivers/src/*.o cpu/src/*.o cpu/src/asm_interrupts/*.o libc/src/*.o  kernel.elf

# Debug target: build with debugging symbols and run QEMU with GDB support
debug: CFLAGS=$(DEBUG_CFLAGS)
debug: os_image.bin kernel.elf
	qemu-system-i386 -s -S -fda os_image.bin &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Release target: build with release flags
release: CFLAGS=$(RELEASE_CFLAGS)
release: all


#steps to debug:
# 1.  /usr/local/cross/bin/i386-elf-gdb
# 2.  target remote :1234
# 3.  symbol-file kernel.elf
# 4.  (optional) layout asm --> set disassembly-flavor intel
# 5.  break ...
# 6.  continue
# 7.  stepi