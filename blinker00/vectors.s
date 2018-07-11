

.section .init
.globl _start
_start:
vec_base: .word 0x40100000
    l32r a2,vec_base
    wsr.vecbase a2
    j .
    call0 notmain
    ill
.balign 0x100
hello: j hello
    nop
    nop
