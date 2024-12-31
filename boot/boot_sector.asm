[bits  16]
[org 0x7c00]

;header - bios block parameter(BPB)
bios_parameter_block:
    bdb_oem:                  db   'BOBO'              ; OEM identifier string
    bdb_bytes_per_sector:     dw   512                 ; Bytes per sector: 512 bytes (standard sector size)
    bdb_sectors_per_cluster:  db   1                   ; Sectors per cluster: 1 (each cluster is one sector)
    bdb_reserved_sectors:     dw   1                   ; Reserved sectors: 1 (reserved for the bootloader and filesystem structures)
    bdb_fat_count:            db   2                   ; Number of FATs: 2 (File Allocation Tables for redundancy)
    bdb_dir_entries_count:    dw   0e0h                ; Number of directory entries: 224 (maximum number of files and directories)
    bdb_total_sectors:        dw   2880                ; Total number of sectors: 2880 (total number of sectors on the disk)
    bdb_media_descriptor_type:db   0f0h                ; Media descriptor type: 0xF0 (indicates a 1.44 MB floppy disk)
    bdb_sectors_per_fat:      dw   9                   ; Sectors per FAT: 9 (number of sectors occupied by each FAT)
    bdb_sectors_per_track:    dw   18                  ; Sectors per track: 18 (number of sectors on each track of the disk)
    bdb_heads:                dw   2                   ; Number of heads: 2 (number of read/write heads on the disk)
    bdb_hidden_sectors:       dd   0                   ; Number of hidden sectors: 0 (no hidden sectors before the start of the FAT)
    bdb_large_sectors_count:  dd   0                   ; Large sectors count: 0 (not used for FAT12, this is set to 0)


boot_start:
    mov [drive_number], dl  ;in bios dl is already set to the drive number.

    mov si, msg_welcome
    call print


%include "boot/diskRead(16bit).asm"
%include "boot/print/print(16bit).asm"
%include "boot/print/print(32bit)_pm.asm"
%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"



drive_number db 0x80 







times 510 - ($-$$) db 0
dw 0xAA55


times 256 dw 0xDADA
times 256 dw 0xFACE