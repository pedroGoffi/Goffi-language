%include "/usr/include/goffiLang/stdGlib.s"
section .text
global _start
_start:
   ;; ---- push int, [value: 10]
   mov  rax, 10
   push rax
   ;; ---- dump
   pop rdi
   call dump
   ;; ---- push int, [value: 1]
   mov  rax, 1
   push rax
   ;; ---- push int, [value: 419]
   mov  rax, 419
   push rax
   ;; ---- add int
   pop  rax
   pop  rbx
   add  rax, rbx
   push rax
   ;; ---- push int, [value: 420]
   mov  rax, 420
   push rax
   ;; ---- equal
   mov rcx, 0
   mov rdx, 1
   pop rax
   pop rbx
   cmp rax, rbx
   cmove rcx, rdx
   push rcx
   ;; ---- if
   pop rax
   test rax, rax
   jz addr_4
  ;; ---- exit, [code: 0]
   mov  eax, 1
   mov  ebx, 0
   int 0x80





addr_4:
   ;; ---- push int, [value: 6969]
   mov  rax, 6969
   push rax
   ;; ---- dump
   pop rdi
   call dump
   ;; ---- exit, [code: 0]
   mov  eax, 1
   mov  ebx, 0
   int 0x80
