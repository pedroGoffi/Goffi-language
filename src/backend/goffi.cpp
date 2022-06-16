#ifndef SRC_SRC_CODE
#define SRC_SRC_CODE 
#include "./goffi.h"
#include "./Lexer.cpp"
#include "Core/Instructions.cpp"
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

#define MEMORY_SIZE 69000
#define makeLabel out << "__label_num__" << addrCount << ":"; ++addrCount;

typedef uint64_t type;
static size_t addrCount = 0;

/*  
 *  This shall simulate the program
 *  using a likely virtual cpu
 *  stack beeing a vector and not std::stack
 *  for better control if i need in future
 *  simulation mode was been removed due to incompatiblity with compile_mode
 */
/*
 * This will compile the program to assembly x86_64
 */
void Goffi::compile_program(std::vector<VR>program, std::string outputFilePath){
    assert(NUM_OF_OPERANDS == 24 && "Exhaustive time handling operand, please update the compile_program in ");

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

    while( ip != program.end()){
        switch(ip->op){
            case OP_GTHAN:
                makeLabel;
                out <<  "   ;; ---- cmpGT\n"
                    <<  "   mov rcx, 0\n"
                    <<  "   mov rdx, 1\n"
                    <<  "   pop rbx\n"
                    <<  "   pop rax\n"
                    <<  "   cmp rax, rbx\n"
                    <<  "   cmovg rcx, rdx\n"
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
                    <<  "   pop rbx\n"
                    <<  "   pop rax\n"
                    <<  "   cmp rax, rbx\n"
                    <<  "   cmovl rcx, rdx\n"
                    <<  "   push rcx\n"
                    ;
                ++ip;
                break;
            case OP_DO: 
                makeLabel;
                out <<  "   ;; ---- do\n"
                    <<  "   pop rax\n"
                    <<  "   test rax, rax\n"
                    <<  "   jz __label_num__" << ip->operand  << "\n"                
                    ;
                ++ip;
                break;
            case OP_END:
                makeLabel;
                out <<  "   ;; ---- end\n"
		    <<	"   jmp __label_num__"
		    ;
		(ip->operand > 0)
		? out << ip->operand
		: out << addrCount;
		out   << "\n";

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
	    case PUSH_STR:
		makeLabel;
		out <<	"   ;; ---- push str\n"
		    <<	"   mov rax, " << ip->op_string.length() << "\n"
		    <<	"   push rax\n"
		    <<	"   push word_string__" << ip->operand << "\n"
		    ;
		++ip;
		break;
	    case OP_DIVMOD: 
		makeLabel;
		out <<	"   ;; ---- divmod\n"
		    <<	"   xor rdx, rdx\n"
		    <<	"   pop rbx\n"
		    <<	"   pop rax\n"
		    <<	"   div rbx\n"
		    <<	"   push rax\n"
		    <<	"   push rbx\n"
		    ;
		++ip;
		break;
	    case OP_IDIVMOD: 
		makeLabel;
		out <<	"   ;; ---- idivmod\n"
		    <<	"   pop rbx\n"
		    <<	"   pop rax\n"
		    <<	"   cqo rbx\n"
		    <<	"   idiv rbx\n"
		    <<	"   push rax\n"
		    <<	"   push rdx\n"
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
	    case OP_MULT:
                makeLabel;
		out <<	"   ;; ---- mult\n"
		    <<	"   pop rax\n"             
		    <<  "   pop rbx\n"             
                    <<  "   mul rbx\n"             
                    <<  "   push rax\n" 
		    ;
		++ip;
		break;
            case OP_MINUS:
                makeLabel;
                out <<  "   ;; ---- minus\n"
                    <<  "   pop rax\n"
                    <<  "   pop rbx\n"
                    <<  "   sub rbx,rax\n"
                    <<  "   push rbx\n"
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
	    case DROP:
		makeLabel;
		out <<	"   ;; ---- drop\n"
		    <<	"   pop rax\n"
		    ;
		++ip;
		break;
	    case SWAP:
		makeLabel;
		out <<	"   ;; ---- swap\n"
		    <<	"   pop rax\n"
		    <<	"   pop rbx\n"
		    <<	"   push rax\n"
		    <<	"   push rbx\n"
		    ;
		++ip;
		break;
	    case OVER:
		makeLabel;
		out <<	"   ;; ---- over\n"
		    <<	"   pop rax\n"
		    <<	"   pop rbx\n"
		    <<	"   push rbx\n"
		    <<	"   push rax\n"
		    <<	"   push rbx\n"
		    ;
		++ip;
		break;
	    case ROT:

		makeLabel;
		out <<	"   ;; ---- rot\n"
		    <<	"   pop rax\n"
		    <<	"   pop rbx\n"
		    <<	"   pop rcx\n"

		    <<	"   push rbx\n"
		    <<	"   push rax\n"
		    <<	"   push rcx\n"
		    ;
		++ip;
		break;
	    case OP_IF:
		makeLabel;
		out <<	"   ;; ---- if\n"; 
                ++ip;
		break;
	    case OP_WHILE:
		makeLabel;
		out <<	"   ;; ---- while\n"; 
                ++ip;
		break;

	    case OP_SYSCALL:
		makeLabel;
		out <<	"   ;; ---- syscall__";
		switch( ip->operand ){
		  case 0:
                    out << "0\n" 
			<< "    pop rax\n"             
			<< "    syscall\n"             
                    	<< "    push rax\n"            
		    	;
		    break;

		  case 1:
                    out <<  "1\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
		    	;
		    break;
		  case 2:
                    out <<  "2\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    pop rsi\n"             
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
		    	;
		    break;
		  case 3:
		    out <<  "3\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    pop rsi\n"             
                    	<<  "    pop rdx\n"             
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
		    	;
		    break;
		  case 4:
                    out <<  "4\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    pop rsi\n"             
                    	<<  "    pop rdx\n"             
                    	<<  "    pop r10\n"             
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
		    	;
		    break;
		  case 5:
                    out <<  "5\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    pop rsi\n"             
                    	<<  "    pop rdx\n"             
                    	<<  "    pop r10\n"             
                    	<<  "    pop r8\n"              
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
		    	;
		    break;
		  case 6:		    
                    out	<<  "6\n"
			<<  "    pop rax\n"             
			<<  "    pop rdi\n"             
                    	<<  "    pop rsi\n"             
                    	<<  "    pop rdx\n"             
                    	<<  "    pop r10\n"             
                    	<<  "    pop r8\n"              
                    	<<  "    pop r9\n"              
                    	<<  "    syscall\n"             
                    	<<  "    push rax\n"            
			;
		    break;
		}
		++ip;
		break;
            case NUM_OF_OPERANDS: break;
            default: {
		makeLabel;
                assert(false && "WARNING! Unreachable operations in compile mode\n");
                ++ip;
                break;
            }
        }
    }
    if( Words.empty() == 0 ){
      out <<  "segment .data\n";
      uint64_t words_count{0};
      for(auto x = Words.begin(); x != Words.end(); ++x){
	out << "  word_string__" << words_count << ":db " << x->second.data() << "\n";
	++words_count;
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
