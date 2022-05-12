#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include "../atom/stack.cpp"
#include "./../../includes/stdGoffi.cpp"
#include "./Panic.cpp"
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <iostream>
#include <string>

enum OpCode: uint8_t {
    /*
     * NOTE: 
     *     @args N can be any value because this will not use it 
     */
    PROCEDURE_ENTRY_POINT,
    MAIN_ENTRY_POINT_SECTION,
    RET,
    OP_CALL,
    EXIT,               // exit N EXITCODE N
    PANIC,              // PANIC N N N

    ADD_INT,            // ADD N N N
    SUB_INT,
    DIV_INT,
    MULT_INT,
    PUSH_INT,           // PUSH_INT N value N
    PUSH_STR,           // PUSH_STR N N string
    PRINT_STR,          // PRINT_STR N N N
    PRINT_INT,          // PRINT_INT N N N

    CMP_INT_LT,         // CMP_INT_LT N N N
    CMP_INT_GT,         // CMP_INT_GT
    CMP_INT_EQU,        // CMP_INT_EQU
    CMP_INT_LTE,        // CMP_INT_LTE
    CMP_INT_GTE,        // CMP_INT_GTE

    LOAD_INT,           // LOAD_INT N N N
    STORE_INT,          // STORE_INT N N N
    JMP_BY_IF_ZERO,     // JMP_BY_IF_ZERO N  jumpLength N
    JMP_BACK,           // JMP_BACK N N N
    DISPLAY,            // DISPLAY N N N
    NUM_INSTRUCTION     // NUM_INSTRUCTION N N N
};


class Instruction
{
    public:
        OpCode op_code;

        uint8_t  ri8;       // register8        interpreted register
        uint16_t ri16;      // register16       interpreted register
        std::string ristr;  // registerstr      interpreted for string

};


namespace testVM{

    std::string VMVersion = "1.0";
    std::string author = "Pedro Henrique goffi de paulo";

    // THIS FUNCTION WILL BE THE CORE OF THE LANGUAGE
    int run(std::vector<Instruction> code){
        //std::cout 
        //    << "This VM is been developed by "
        //    << testVM::author
        //    << "\nVersion: "
        //    << testVM::VMVersion 
        //    << "\n";

        class stack<int16_t> stackVM(1024);
        //std::vector<Instruction>::iterator ip = code.begin();


        // ByteCodeInterpreted 
        auto ip  = code.begin();
        auto end = code.end();
        gassert(NUM_INSTRUCTION == 20, "New functions not implemented in the Interpreter");
        while(ip != end){
            switch(ip->op_code)
            {

                case MAIN_ENTRY_POINT_SECTION:
                    break;
                // DISPLAY N N N
                // DISPLAY all the stack : usage on debuging
                case DISPLAY:
                    while(stackVM.Len() > 0){
                        std::cout << stackVM.pop() << ", ";
                    }
                    ++ip;
                    break;


                // EXIT N exit_code N 
                // exit with exit_code exit code
                case EXIT:
                    exit(ip->ri16);
                    break;


                // PANIC N N N
                // will send a message to the console output
                // telling that in <this> position
                // something went wrong
                case PANIC: {
                                /*  TODO:
                                 *      SWITCH CASE WITH RI8 FOR OPTIONAL
                                 *      EXTIS OR NOTH
                                 */
                                throw Panic(ip->ri16, ip->ristr);
                                exit(ip->ri16);
                                break;
                            }


                // PRINT_INT N N N
                // PRINT THE LAST ELEMENT OF THE STACK
                case PRINT_INT:{                                
                                std::cout << stackVM.pop();
                                ++ip;
                                break;
                                }


                // ADD_INT N N N
                // ADD THE LAST TWO ELEMENTS OF THE STACK
                case ADD_INT:{
                                int16_t RHS = stackVM.pop();
                                stackVM.push(stackVM.pop()+RHS);
                                ++ip;
                                break;
                             }


                // PUSH_STR N N STR
                // PUSH STR FOR THE TEMPORARY BUFFER
                case PUSH_STR: {
                                    stackVM.buffer(ip->ristr);
                                    ++ip;
                                    break;
                                }


                // PRINT_STR N N N
                // WILL PRINT THE TEMPORARY BUFFER
                case PRINT_STR: {  
                                  std::cout << stackVM.buffer_value;
                                  ++ip;
                                  break;
                                }


                // PUSH_INT N value N
                // WILL BRING TO THE TOP OF THE STACK value
                case PUSH_INT:
                    stackVM.push(ip->ri16);
                    ++ip;
                    break;


                // CMP_INT_LT N N N
                // WILL COMPARE THE LAST TWO ELEMENTS OF THE STACK IF .POP_1
                // IS BIGGER THAN THE .POP_2
                // BECAUSE ON THE STACK THEY LOOKS LIKE X_1 X_2
                // IF X_1 < X_2
                // THEN POP_1 = X_2
                // AND  POP_2 = X_1                
                // IF X_1 < X_2 THEN POP_1 > POP_2
                // THEN FINALLY WILL BRING TO THE TOP OF THE STACK 1 IF IT IS
                // TRUE OR 0 IF IT IS FALSE
                case CMP_INT_LT: {
                                   int16_t ans = (stackVM.pop()  > stackVM.pop())? 1 : 0;
                                   stackVM.push(ans);
                                   ++ip;
                                   break;
                                 }


                // CMP_INT_GT N N N
                // WILL COMPARE THE LAST TWO ELEMENTS OF THE STACK IF .POP_1
                // IS LESS THAN THE .POP_2
                // BECAUSE ON THE STACK THEY LOOKS LIKE X_1 X_2
                // IF X_1 < X_2
                // THEN POP_1 = X_2
                // AND  POP_2 = X_1                
                // IF X_1 > X_2 THEN POP_1 < POP_2
                // THEN FINALLY WILL BRING TO THE TOP OF THE STACK 1 IF IT IS
                // TRUE OR 0 IF IT IS FALSE
                case CMP_INT_GT: {
                                     int16_t ans = (stackVM.pop() < stackVM.pop())? 1 : 0;
                                     stackVM.push(ans);
                                     ++ip;
                                     break;
                                 }



                // CMP_INT_EQU N N N
                // WILL COMPARE THE LAST TWO ELEMENTS OF THE STACK IF .POP_1
                // IS EQUAL THAN THE .POP_2
                // BECAUSE ON THE STACK THEY LOOKS LIKE X_1 X_2
                // IF X_1 < X_2
                // THEN POP_1 = X_2
                // AND  POP_2 = X_1                
                // IF X_1 == X_2 THEN POP_1 == POP_2
                // THEN FINALLY WILL BRING TO THE TOP OF THE STACK 1 IF IT IS
                // TRUE OR 0 IF IT IS FALSE
                case CMP_INT_EQU: {
                                      int16_t ans = (stackVM.pop() == stackVM.pop())? 1 : 0;
                                      stackVM.push(ans);
                                      ++ip;
                                      break;
                                  }


                // CMP_INT_LTE N N N
                // WILL COMPARE THE LAST TWO ELEMENTS OF THE STACK IF .POP_1
                // IS BIGGER OR EQUAL THAN THE .POP_2
                // BECAUSE ON THE STACK THEY LOOKS LIKE X_1 X_2
                // IF X_1 =< X_2
                // THEN POP_1 = X_2
                // AND  POP_2 = X_1                
                // IF X_1 =< X_2 THEN POP_1 => POP_2
                // THEN FINALLY WILL BRING TO THE TOP OF THE STACK 1 IF IT IS
                // TRUE OR 0 IF IT IS FALSE
                case CMP_INT_LTE: {
                                      int16_t ans = (stackVM.pop() >= stackVM.pop())? 1 : 0;
                                      stackVM.push(ans);
                                      ++ip;
                                      break;
                                  }


                // CMP_INT_GTE N N N
                // WILL COMPARE THE LAST TWO ELEMENTS OF THE STACK IF .POP_1
                // IS BIGGER THAN THE .POP_2
                // BECAUSE ON THE STACK THEY LOOKS LIKE X_1 X_2
                // IF X_1 >= X_2
                // THEN POP_1 = X_2
                // AND  POP_2 = X_1                
                // IF X_1 >= X_2 THEN POP_1 <= POP_2
                // THEN FINALLY WILL BRING TO THE TOP OF THE STACK 1 IF IT IS
                // TRUE OR 0 IF IT IS FALSE
                case CMP_INT_GTE: {
                                      int16_t ans = (stackVM.pop() <= stackVM.pop())? 1 : 0;
                                      stackVM.push(ans);
                                      ++ip;
                                      break;
                                  }


                // LOAD_INT WILL BRING TO THE TOP OF THE STACK THE VARIABLE
                // WITH THE NAME OF THE TEMPORARY BUFFER
                case LOAD_INT:{
                                stackVM.push(stackVM.loadAt(stackVM.buffer_value));
                                ++ip;
                                break;
                              }


                // STORE_INT WILL STORE THE VARIABLE OF INTEGER TYPE WIDTH THE
                // NAME IN THE TEMPORARY BUFFER INSIDE THE STACK HASH MAP
                case STORE_INT: {
                                  stackVM.storeAt(stackVM.buffer_value, stackVM.pop());
                                  ++ip;
                                  break;                              
                                }
                

                // JMP_BY_IF_ZERO N  jumpLength N
                // WILL JUMP jumpLength EVERYTIME STACK HAS VALUE OF 1 THAT
                // MEANS TRUE
                case JMP_BY_IF_ZERO: {
                                       if (stackVM.pop() == 0) {
                                           ip += ip->ri16;
                                       } else {
                                           ++ip;
                                       }
                                       break;
                                     }


                // JMP_BACK N jumpLength
                // WILL JUMP BACK ALWAYS jumpLength STEPS
                case JMP_BACK: {
                                 ip -= ip->ri16;
                                 break;
                               }


                // USAGE FOR ENUM HOW MUCH INSTRUCTION THIS HAS
                case NUM_INSTRUCTION:
                                break;


                default:
                                exit(1);

            }
        } 

        return 0;

    }
}
#endif /* ifndef INSTRUCTIONS */
