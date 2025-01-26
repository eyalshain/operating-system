;having an entry point for kernel execution.
[bits 32]
[extern kmain]

call kmain
jmp $