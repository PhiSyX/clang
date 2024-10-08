.set MAGIC, 0x1BADB002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)


.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text 
.extern kernel_main
.extern call_ctors
.global loader


loader:
    mov $kernel_stack, %esp
    call call_ctors
    push %eax
    push %ebx
    call kernel_main


_stop:
    cli
    hlt
    jmp _stop


.section .bss
.space 2*1024*1024 ; # 2MiB
kernel_stack:
