        .file   "example.c"
        .text
        .globl  main
        .p2align        4
        .type   main,@function
main:
        .cfi_startproc
        pushq   %rax
        .cfi_def_cfa_offset 16
        leaq    .Lstr(%rip), %rdi
        callq   puts@PLT
        xorl    %eax, %eax
        popq    %rcx
        .cfi_def_cfa_offset 8
        retq
.Lfunc_end0:
        .size   main, .Lfunc_end0-main
        .cfi_endproc

        .type   .Lstr,@object
        .section        .rodata.str1.1,"aMS",@progbits,1
.Lstr:
        .asciz  "Hello, World!"
