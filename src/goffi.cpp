#ifndef SRC_SRC_CODE
#define SRC_SRC_CODE 
#include "./goffi.h"
#include <vector>
#include <cassert>
#include <fstream>

#define MEMORY_SIZE 69000
#define makeLabel out << "addr_" << addrCount << ":\n"; ++addrCount;

typedef uint64_t type;
/*  
 *  This shall simulate the program
 *  using a likely virtual cpu
 *  stack beeing a vector and not std::stack
 *  for better control if i need in future
 */
void Goffi::simulate_program(std::vector<VR> &program){
    assert(NUM_OF_OPERANDS == 17 && "Exhaustive time handling operand, please update the simulate_program");
    // IF BLOCKS
    // if in sim mode is only sintax 
    // in com mode it create a label to perform jumps
    // do points to (elif or else)+1 if expr false
    // elif | else points to elif or end
    //
    // if expr do       
    //      <block>
    //      <block>
    //      <block>
    // elif expr do
    //      <block>
    //      <block>
    //      <block>
    // else 
    //      <block>
    //      <block>
    //      <block>
    // end
    std::vector<VR>::iterator ip = program.begin();
    std::vector<uint64_t> stack(258);

    while(ip != program.end()){
        switch(ip->op){
            case OP_LOADBYTE:
                ++ip;
                assert(false && "Not implemented yet\n");
                break;
            case OP_STOREBYTE:
                ++ip;
                assert(false && "Not implemented yet\n");
                break;
            case OP_MEM:{
                ++ip;
                assert(false && "Not implemented yet\n");
                break;
            }
            case OP_GTHAN:{
                type a = stack.back(); 
                stack.pop_back();
                type b = stack.back(); 
                stack.pop_back();

                stack.push_back( a < b );
                ++ip;
                break;
            }

            case OP_LTHAN:{
                type a = stack.back(); 
                stack.pop_back();
                type b = stack.back(); 
                stack.pop_back();

                stack.push_back( a > b );                
                ++ip;
                break;
            }
            case WHILE:
                ++ip;
                break;
            case DUP:{
                type a = stack.back();
                stack.pop_back();

                stack.push_back(a);
                stack.push_back(a);
                ++ip;
                break;

            }
            case OP_IF:
                ++ip;
                break;
            case OP_DO:{
                type a = stack.back();
                stack.pop_back();
                if(a == 0){
                    ip += ip->operand;
                }
                else{
                    ++ip;
                }
                break;
            }
            case OP_ELSE:{
                    ip += ip->operand;
                    break;
            }
            case OP_END:                         
                if(ip->operand > 0){
                    ip -= ip->operand;
                }
                else
                    ++ip;                
                break;

            case OP_EQUALS:{
                type a = stack.back();
                stack.pop_back();
                type b = stack.back();
                stack.pop_back();
                stack.push_back( b == a );
                ++ip;
                break;
            }
            case PUSH_INT:
                stack.push_back(ip->operand);
                ++ip;
                break;
            case OP_PLUS:{
                type a = stack.back();
                stack.pop_back();
                type b = stack.back();
                stack.pop_back();
                stack.push_back(b + a);
                ++ip;
                break;
            }
            case OP_MINUS:{
                type a = stack.back();
                stack.pop_back();
                type b = stack.back();
                stack.pop_back();
                stack.push_back(b - a);
                ++ip;
                break;
            }
            case DUMP:{
                type a = stack.back();
                stack.pop_back();
                printf("%ld\n", a);
                ++ip;
                break;
            }
            case EXIT:
                exit(static_cast<int>(ip->operand));
                ip = program.end();
                break;
            case NUM_OF_OPERANDS: break;
            default: {
                assert(false && "WARNING!! Unreachable operation in simulation mode\n");
                break;
            }
        }
    }
}
/*
 * This will compile the program to assembly x86_64
 */
void Goffi::compile_program(std::vector<VR>program, std::string outputFilePath){
    assert(NUM_OF_OPERANDS == 17 && "Exhaustive time handling operand, please update the compile_program in ");

    std::fstream out("out.asm", std::ios::out);


    /*  TODO:
     *      Include by ip
     */
    out <<  "%include \"/usr/include/goffiLang/stdGlib.s\"\n"
        <<  "global _start\n"
        <<  "segment .text\n"
        <<  "_start:\n"
        ;
    std::vector<VR>::iterator ip = program.begin();
    size_t addrCount = 0;
    while( ip != program.end()){
        switch(ip->op){
            case OP_GTHAN:
                makeLabel;
                out <<  "   ;; ---- cmpGT\n"
                    <<  "   mov rcx, 0\n"
                    <<  "   mov rdx, 1\n"
                    <<  "   pop rax\n"
                    <<  "   pop rbx\n"
                    <<  "   cmp rax, rbx\n"
                    <<  "   cmove rcx, rdx\n"
                    <<  "   push rcx\n"
                    ;
                ++ip;
                break;
            case DUP:
                makeLabel;
                out <<  "   ;; ---- dup\n"
                    <<  "   pop rax\n"
                    <<  "   push rax\n"
                    <<  "   push rax\n"
                    ;
                ++ip;
                break;
            case OP_STOREBYTE:{

                makeLabel;
                switch(ip->operand){
                    case (8):

                        out <<  "   ;; ---- store 8\n"
                            <<  "   pop rbx\n"
                            <<  "   pop rax\n"
                            <<  "   mov BYTE [rax], bl\n"
                            ;
                        break;
                }
                ++ip;
                break;
            }
            case OP_LOADBYTE: {
                makeLabel;
                switch(ip->operand){
                    case (8):
                        out <<  "   ;; ---- load 8\n"
                            <<  "   pop rax\n"
                            <<  "   xor rbx, rbx\n"
                            <<  "   mov bl, BYTE [rax]\n"
                            <<  "   push rbx\n"
                            ;
                        break;
                }
                ++ip;
                break;
            }
            case OP_MEM:
                makeLabel;
                out <<  "   ;; ---- mem\n"
                    <<  "   push buffer\n"
                    ;
                ++ip;
                break;
            case OP_LTHAN:
                makeLabel;
                out <<  "   ;; ---- cmp LT\n"
                    <<  "   mov rcx, 0\n"
                    <<  "   mov rdx, 1\n"
                    <<  "   pop rax\n"
                    <<  "   pop rbx\n"
                    <<  "   cmp rbx, rax\n"
                    <<  "   cmovl rcx, rdx\n"
                    <<  "   push rcx\n"
                    ;
                ++ip;
                break;
            case WHILE:
                makeLabel;
                out <<  "   ;; ---- while\n"
                    ;
                ++ip;
                break;
            case OP_IF: 
                makeLabel;
                out <<  "   ;; ---- if\n"
                    ;
                ++ip;
                break;
            case OP_ELSE: 
                makeLabel;
                out <<  "   jmp addr_" << ip->operand  << "\n"
                    <<  "   ;; ---- else\n"
                    ;
                ++ip;
                break;
            case OP_DO: 
                makeLabel;
                out <<  "   ;; ---- do\n"
                    <<  "   pop rax\n"
                    <<  "   test rax, rax\n"
                    <<  "   jz addr_" << ip->operand << "\n"                
                    ;
                ++ip;
                break;
            case OP_END:
                makeLabel;
                out <<  "   ;; ---- end\n";
                if(ip->operand > 0){
                    out
                        <<  "   jmp  addr_"     << ip->operand  << "\n"
                        ;
                }else{
                    out <<  "   jmp addr_"      << addrCount    << "\n"
                        ;
                }

                ++ip;
                break;
            case OP_EQUALS:
                makeLabel;
                out <<  "   ;; ---- equals\n"
                    <<  "   mov rcx, 0\n"
                    <<  "   mov rdx, 1\n"
                    <<  "   pop rax\n"
                    <<  "   pop rbx\n"
                    <<  "   cmp rax,rbx\n"
                    <<  "   cmove rcx, rdx\n"
                    <<  "   push rcx\n"
                    ;
                ++ip;
                break;
            case PUSH_INT:
                makeLabel;
                out <<  "   ;; ---- push int\n"
                    <<  "   push " << ip->operand << "\n"
                    ;
                ++ip;
                break;
            case OP_PLUS:{
                makeLabel;
                out <<  "   ;; ---- add\n"
                    <<  "   pop rbx\n"
                    <<  "   pop rax\n"
                    <<  "   add rax, rbx\n"
                    <<  "   push rax\n"
                    ;
                ++ip;
                break;
            }
            case OP_MINUS:
                makeLabel;
                out <<  "   ;; ---- minus\n"
                    <<  "   pop rbx\n"
                    <<  "   pop rax\n"
                    <<  "   sub rax,rbx\n"
                    <<  "   push rax\n"
                    ;
                ++ip;
                break;
            case DUMP:{
                makeLabel;
                out <<  "   ;; ---- call dump\n"
                    <<  "   pop rdi\n"
                    <<  "   call dump\n"
                    ;
                ++ip;
                break;
            }
            case EXIT:
                makeLabel;
                out <<  "   ;; --- exit\n"
                    <<  "   mov rax, 60\n"
                    <<  "   mov rdi, " << ip->operand << "\n"
                    <<  "   syscall\n"
                    ;
                ++ip;
                break;
            case NUM_OF_OPERANDS: break;
            default: {
                assert(false && "WARNING! Unreachable operations in compile mode\n");
                ++ip;
                break;
            }
        }
    }
    out <<  "segment .bss\n"
        <<  "buffer:    resb    " << MEMORY_SIZE << "\n"
        ;
    out.close();
    char cmd[128];
    sprintf(cmd, "nasm -felf64 -g out.asm");
    system(cmd);

    sprintf(cmd, "ld out.o -o %s", outputFilePath.c_str());
    system(cmd);

    //sprintf(cmd, "rm out.o");
    //system(cmd);

}
#endif /* ifndef SRC_SRC_CODE */
