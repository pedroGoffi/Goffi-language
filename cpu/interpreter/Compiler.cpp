#ifndef COMPILER_CPP
#define COMPILER_CPP 
#include "./Compiler.h"
#include "./../../includes/stdGoffi.cpp"
#include "./../../main.cpp"
#include <fstream>
#define PORCENTAGE_SYMBOL char(0x25)

/*  NOTE:
 *      COMPILER STAGE
 *      AFTER PARSING THE CODE IT WILL SEND HERE AN VECTOR OF INSTRUCTIONS
 *      THAT WILL BE USED TO MAKE ASSEMBLY LINE BY LINE
 *
 * TODO:
 *      CREATE A SECUNDARY ARGUMENT TO HANDLE THE CONTEXT CODE
 *
 * OPTIONAL:
 *      PARSE AN MAIN FUNCTION
 */

void testVM::compile_asm(std::vector<Instruction> code){
    /*  NOTE:
     *      CODE IS GIVEN BY THE PARSER
     *      THE PARSER CAN EMULATE THE CODE OR SEND TO HERE TO COMPILE THE
     *      CODE ITSELF
     */
    /*  TODO:
     *      -[x] CREATE THE OUTPUT FILE 
     *      -[] WALK THRU THE CODE VECTOR AND DUMP INTO THE OUTPUT FILE
     *      -[] TRANSLATE EACH OP_CODE TO ASSEMBLY FILE
     */
    /*  CREATING THE FILE */
    std::string     file_name("out.asm");
    std::fstream    out;
    /*  NOTE:
     *      THIS SHALL ASSERT THE FILE INITIALY WILL BE EMPTY
     */
    out.open(file_name, std::ios_base::out);

    // note PORCENTAGE_SYMBOL is a macro equal
    // char(0x25) == %
    // somehow this has a bug when i do `%%` by writing two `%`
    
    out <<  PORCENTAGE_SYMBOL 
        <<  "include \"/usr/include/goffiLang/stdGlib.s\"\n"
        <<  "section .text\n"
        <<  "global _start\n"
        ;
    out.close();
    out.open(file_name, std::ios_base::app);

    gassert(out.is_open(), "Could not create the assembly file");
    gassert(NUM_INSTRUCTION == 26, "New functions not implemented in the compiler");

    for(auto& op : code){
        switch(op.op_code){

            /*  PUSH_INT op:
             *      THIS WILL PUSH THE ARGUMENT TO THE STACK
             */
            case IF: {
                out <<  "   ;; ---- if\n"
                    <<  "   pop rax\n"
                    <<  "   test rax, rax\n"
                    <<  "   jz addr_"       << op.ri16 << "\n"
                    ;                
                break;
            }
            case PROCEDURE_ENTRY_POINT:
                out << op.ristr << ":\n";
                break;
            case OP_CALL:
                // TODO arg parse
                out <<  "   ;; ---- call "  << op.ristr <<  "\n"
                        "   call "          << op.ristr <<  "\n"
                    ;
                break;
            case MAIN_ENTRY_POINT_SECTION:
                out <<  "_start:\n";
                break;
            case PUSH_INT:
                out <<  "   ;; ---- push int, [value: "  << op.ri16  << "]\n"
                        "   mov  rax, "     << op.ri16  << "\n"
                        "   push rax\n"
                    ;
                break;


            /* ADD_INT op:
             *      THIS WILL ADD THE LAST TWO DIGITS IN THE STACK BY POPING
             *      THEM
             */
            case ADD_INT:
                out <<  "   ;; ---- add int\n"
                        "   pop  rax\n"
                        "   pop  rbx\n"
                        "   add  rax, rbx\n"
                        "   push rax\n"
                    ;
                break;


            /*  SUB_INT op:
             *      THIS WILL SUBTRACT THE LAST TWO DIGITS IN THE STACK BY
             *      POPING THEM
             */
            case SUB_INT:
                out <<  "   ;; ---- sub int\n"
                        "   pop rax\n"
                        "   pop rbx\n"
                        "   sub rax, rbx\n"
                        "   push rax\n"
                    ;
                break;
            case DIV_INT:
                gassert(false, "OP DIV_INT not implementet yet");
                break;
            case MULT_INT:
                gassert(false, "OP MULT_INT not implementet yet");
                break;
            case PUSH_STR:
                gassert(false, "OP PUSH_STR not implemented yet");
                break;
            case PRINT_STR:
                gassert(false, "OP PRINT_STR not implementet yet");
                break;
            case PRINT_INT:
                out <<  "   ;; ---- dump\n"
                        "   pop rdi\n"
                        "   call dump\n"

                    ;
                break;
            case EQUALS:
                out <<  "   ;; ---- equal\n"
                        "   mov rcx, 0\n"
                        "   mov rdx, 1\n"
                        "   pop rax\n"
                        "   pop rbx\n"
                        "   cmp rax, rbx\n"
                        "   cmove rcx, rdx\n"
                        "   push rcx\n"
                    ;
                break;
            case CMP_INT_GT:
                gassert(false, "COMPARASIONS OP not implementet yet");
                break;
            case CMP_INT_EQU:
                gassert(false, "COMPARASIONS OP not implementet yet");
                break;
            case CMP_INT_LTE:
                gassert(false, "COMPARASIONS OP not implementet yet");
                break;
            case CMP_INT_GTE:
                gassert(false, "COMPARASIONS OP not implementet yet");
                break;
            case CMP_INT_LT:
                gassert(false, "COMPARASIONS OP not implementet yet");
                break;
            case LOAD_INT:
                gassert(false, "OP LOAD_INT not implementet yet");
                break;
            case STORE_INT:
                gassert(false, "OP STORE_INT not implementet yet");
                break;
            case JMP_BY_IF_ZERO:
                gassert(false, "OP JMP_BY_IF_ZERO not implementet yet");
                break;
            case JMP_BACK:
                gassert(false, "OP JMP_BACK not implementet yet");
                break;
            case DISPLAY:
                gassert(false, "OP DISPLAY not implementet yet");
                break;
            case NUM_INSTRUCTION:
                /*  NOTE:
                 *      THIS IS HERE JUST WHEN COMPILE DONT ACTIVATE FLAGS FOR
                 *      "HANDLE THIS CODE"
                 */
                break;
            case EXIT:
                out <<  "   ;; ---- exit, [code: "  << op.ri16  << "]\n"
                        "   mov  eax, 1\n"
                        "   mov  ebx, "             <<  op.ri16 << "\n"
                        "   int 0x80\n"
                    ; 
                break;
            case RET:
                out <<  "   ;; ---- return\n"
                    <<  "   ret\n"
                    ;
                break;
            default:
                gassert(false, "Unreachable operand type, not implemented in the compiler");
        }
    }
    out.close();
    //out <<  "section .data\n";
    //
    system("nasm -felf64 out.asm -o bin.goffi.o && ld bin.goffi.o -o bin.goffi");
    system("rm bin.goffi.o");
}
#endif /* ifndef COMPILER_CPP */
