C_SOURCE = $(wildcard kernel/*.c  drivers/src/*.c drivers/src/*.c libc/src/*.c)
HEADERS = $(wildcard kernel/*.h drivers/include/*.h libc/include/*.h)

CROSS_COMPILER = /usr/local/cross/bin/i386-elf
OBJ = ${C_SOURCE:.c=.o}	


CC = $(CROSS_COMPILER)-gcc
LD = $(CROSS_COMPILER)-ld
GDB = $(CROSS_COMPILER)-gdb 



run: all
	qemu-system-i386 -fda os_image.bin

all: os_image.bin

#building the os image file
os_image.bin: boot/boot_sector.bin kernel.bin
	cat $^ > $@

#linking the kernel
kernel.bin: boot/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary


#rule to build the boot sector in the boot folder
boot/boot_sector.bin: boot/boot_sector.asm 
	nasm $< -f bin -o $@



#rule to build the kernel entry in the boot folder
boot/kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf32 -o $@


%.o : %.c ${HEADERS}
	$(CC) -g -ffreestanding -m32 -fno-pic -c $< -o $@

%.o : %.asm
	nasm $< -f elf32 -o $@



clean: 
	rm -fr build/*.bin build/*.o *.bin *.o os_image
	rm -fr kernel/*.o boot/*.bin boot/*.o drivers/*.o 
