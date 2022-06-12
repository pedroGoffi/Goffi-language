%include "/usr/include/goffiLang/stdGlib.s"
global _start
segment .text
_start:
__label_num__0:   ;; ---- push int
   push 1
__label_num__1:   ;; ---- push int
   push 1
__label_num__2:   ;; ---- while
__label_num__3:   ;; ---- dup
   pop rax
   push rax
   push rax
__label_num__4:   ;; ---- push int
   push 6
__label_num__5:   ;; ---- cmp LT
   mov rcx, 0
   mov rdx, 1
   pop rax
   pop rbx
   cmp rbx, rax
   cmovl rcx, rdx
   push rcx
__label_num__6:   ;; ---- do
   pop rax
   test rax, rax
   jz __label_num__14
__label_num__7:   ;; ---- dup
   pop rax
   push rax
   push rax
__label_num__8:   ;; ---- rot
   pop rax
   pop rbx
   pop rcx
   push rbx
   push rax
   push rcx
__label_num__9:   ;; ---- mult
   pop rax
   pop rbx
   mul rbx
   push rax
__label_num__10:   ;; ---- swap
   pop rax
   pop rbx
   push rax
   push rbx
__label_num__11:   ;; ---- push int
   push 1
__label_num__12:   ;; ---- add
   pop rbx
   pop rax
   add rax, rbx
   push rax
__label_num__13:   ;; ---- end
   jmp __label_num__3
__label_num__14:   ;; ---- drop
   pop rax
__label_num__15:   ;; ---- call dump
   pop rdi
   call dump
segment .bss
buffer:    resb    69000
