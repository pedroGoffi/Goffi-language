#ifndef COMPILER_CPP
#define COMPILER_CPP 
#include "./Compiler.h"
#include "./../../includes/stdGoffi.cpp"
#include <fstream>

void testVM::compile_asm(std::vector<Instruction> code){
    /*  TODO:
     *      -[x] CREATE THE OUTPUT FILE 
     *      -[] WALK THRU THE CODE VECTOR AND DUMP INTO THE OUTPUT FILE
     *      -[] AT THIS POINT I'LL ONLY NEED TO TRANSLATE TO ASSEMBLY x86_64
     */
    /*  CREATING THE FILE */
    std::string     file_name("out.asm");
    std::fstream    out;
    out.open(file_name, std::ios_base::out);
    /*  CREATE AN EMPTY FILE */


    out <<  "section .text\n"
        <<  "global _start\n"
        <<  "_start:\n"
    ;

    out.close();
    out.open(file_name, std::ios_base::app);

    gassert(out.is_open(), "Could not create the assembly file");

    for(auto& op : code){
        switch(op.op_code){
            case PUSH_INT:
                out <<  "   ;; ---- push int "  << op.ri16  << "\n"
                        "   mov  rax, "          << op.ri16  << "\n"
                        "   push rax\n"
                    ;
                break;
            case ADD_INT:
                out <<  "   ;; ---- add int\n"
                        "   pop  rax\n"
                        "   mov  rbx, rax\n"
                        "   pop  rax\n"
                        "   add  rbx, rax\n"
                        "   push rax\n"
                    ;
                break;
            case PRINT_INT:
                break;
            case EXIT:
                out <<  "   ;; ---- exit\n"
                        "   mov  eax, 1\n"
                        "   mov  ebx, "   <<  op.ri16 << "\n"
                        "   int 0x80\n"
                    ; 
                break;

        }
    }
    out.close();
    //out <<  "section .data\n";
    //
    system("nasm -felf64 out.asm -o bin.goffi.o && ld bin.goffi.o -o bin.goffi");
    system("rm bin.goffi.o");
}
#endif /* ifndef COMPILER_CPP */
