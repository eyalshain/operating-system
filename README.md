#**Operating system!**

EyalOS is a lightweight operating system built from scratch, designed to run on x86 architectures. It features a custom bootloader, kernel, basic drivers, and interrupt handling, showcasing low-level programming and operating system development.

Features

Boot Process: Starts in 16-bit real mode and transitions to 32-bit protected mode using a Global Descriptor Table (GDT).

Interrupt Handling: Implements an Interrupt Descriptor Table (IDT) with custom Interrupt Service Routines (ISR) for exceptions and hardware interrupts.

Drivers:

Screen Driver: Provides basic text output to the console.

Port I/O Driver: Enables interaction with hardware using IN/OUT instructions.

Memory Management: Basic memory handling using segment registers and low-level stack operations.

Emulation & Testing: Runs on QEMU for easy debugging and testing