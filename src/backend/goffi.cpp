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
 */
void Goffi::simulate_program(std::vector<VR> &program){
    assert(NUM_OF_OPERANDS == 21 && "Exhaustive time handling operand, please update the simulate_program");

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
                assert(false && "MEM Not implemented yet\n");
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
            case DUP:{
                type a = stack.back();
                stack.pop_back();

                stack.push_back(a);
                stack.push_back(a);
                ++ip;
                break;

            }
            case OP_DO:{
                type a = stack.back();
                stack.pop_back();

                if(a){
                    ++ip;
                }
                else{
                    ip = program.begin() + (int)ip->operand;

                }
                break;
            }
            case OP_END:
                if(ip->operand > 0){
                    ip = program.begin() + int(ip->operand);
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
	    case OP_MULT: {
		type a = stack.back();
		stack.pop_back();
		type b = stack.back();
		stack.pop_back();
		stack.push_back(b * a);
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
	    case DROP:
		stack.pop_back();
		++ip;
		break;
	    case SWAP:{
		type a = stack.back(); stack.pop_back();
		type b = stack.back(); stack.pop_back();
		stack.push_back(a);
		stack.push_back(b);

		++ip;
	    } break;
	    case OVER:{
		type a = stack.back(); stack.pop_back();
		type b = stack.back(); stack.pop_back();
		stack.push_back(b);
		stack.push_back(a);
		stack.push_back(b);
		++ip;
	    } break;
	    case ROT:{
		type a = stack.back(); stack.pop_back();
		type b = stack.back(); stack.pop_back();
		type c = stack.back(); stack.pop_back();

		stack.push_back(b);
		stack.push_back(a);
		stack.push_back(c);
		++ip;
	    } break;
	    case OP_SYSCALL:
	      fprintf(stderr, "SYSCALLS are not implemented in simulation mode yet\n");
	      exit(1);
	      ++ip;
	      break;
	    case OP_IF:
	    case OP_WHILE:
            case NUM_OF_OPERANDS: 
            default: {
                ++ip;
                break;
            }
        }
    }
}
/*
 * This will compile the program to assembly x86_64
 */
void Goffi::compile_program(std::vector<VR>program, std::string outputFilePath){
    assert(NUM_OF_OPERANDS == 21 && "Exhaustive time handling operand, please update the compile_program in ");

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
