sort_array(int*, int):
        lea     edx, [rsi-1]
        mov     r8, rdi
        test    edx, edx
        jle     .L1
        lea     r9, [rdi+4]
.L6:
        sub     edx, 1
        mov     rax, r8
        mov     rdi, rdx
        lea     rsi, [r9+rdx*4]
.L3:
        mov     edx, DWORD PTR [rax]
        mov     ecx, DWORD PTR [rax+4]
        cmp     edx, ecx
        jle     .L5
        mov     DWORD PTR [rax], ecx
        mov     DWORD PTR [rax+4], edx
.L5:
        add     rax, 4
        cmp     rsi, rax
        jne     .L3
        mov     edx, edi
        test    edi, edi
        jne     .L6
.L1:
        ret
