global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


;ISRS for hardware interrupts

irq0:
    cli
    push dword 32
    call irq_common_stub

irq1:
    cli
    push dword 33
    call irq_common_stub

irq2:
    cli
    push dword 34
    call irq_common_stub

irq3:
    cli
    push dword 35
    call irq_common_stub

irq4:
    cli
    push dword 36
    call irq_common_stub

irq5:
    cli
    push dword 37
    call irq_common_stub

irq6:
    cli
    push dword 38
    call irq_common_stub

irq7:
    cli
    push dword 39
    call irq_common_stub

irq8:
    cli
    push dword 40
    call irq_common_stub

irq9:
    cli
    push dword 41
    call irq_common_stub

irq10:
    cli
    push dword 42
    call irq_common_stub

irq11:
    cli
    push dword 43
    call irq_common_stub

irq12:
    cli
    push dword 44
    call irq_common_stub

irq13:
    cli
    push dword 45
    call irq_common_stub

irq14:
    cli
    push dword 46
    call irq_common_stub

irq15:
    cli
    push dword 47
    call irq_common_stub
