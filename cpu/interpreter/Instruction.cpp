#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include "../atom/stack.cpp"
#include <cstdint>
#include <iostream>
#include <string>

enum OpCode: uint8_t {
    // N can be any value because this will not use it 
    EXIT,               // exit N EXITCODE N
    ADD_INT,            // ADD N N N
    PUSH_INT,           // PUSH_INT N value N
    PUSH_STR,           // PUSH_STR N N string
    PRINT_STR,          // PRINT_STR N N N
    PRINT_INT,          // PRINT_INT N N N
    CMP_INT_LT,         // CMP_INT_LT N N N
    LOAD_INT,           // LOAD_INT N N N
    STORE_INT,          // STORE_INT N N N
    JMP_BY_IF_ZERO,     // JMP_BY_IF_ZERO N N jumpLength
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
    int run(Instruction code[])
    {
        std::cout 
            << "This VM is been developed by "
            << testVM::author
            << "\nVersion: "
            << testVM::VMVersion 
            << "\n";

        class stack<int16_t> stackVM(1024);
        class Instruction *ip = code;

        // ByteCodeInterpreted 
        while(ip != nullptr)
        {
            switch(ip->op_code)
            {

                // DISPLAY N N N
                // DISPLAY all the stack : usage on debuging
                case DISPLAY:
                    while(1){
                        std::cout << stackVM.pop() << ", ";
                        break;
                    }


                // EXIT N exit_code N 
                // exit with exit_code exit code
                case EXIT:
                    ip = nullptr;
                    //exit(ip->ri16);

                    break;


                // PRINT_INT N N N
                // PRINT THE LAST ELEMENT OF THE STACK
                case PRINT_INT:{                                
                                 std::cout <<"[PRINT]: value = "<< stackVM.last() << "\n";
                                 ++ip;
                                 break;
                               }

                // ADD_INT N N N
                // ADD THE LAST TWO ELEMENTS OF THE STACK
                case ADD_INT:{
                                std::cout << "[ADD_INT]: value = ";
                                int16_t RHS = stackVM.pop();
                                stackVM.push(stackVM.pop()+RHS);
                                std::cout << stackVM.last() << "\n";
                                ++ip;                            
                                break;
                             }


                // PUSH_STR N N STR
                // PUSH STR FOR THE TEMPORARY BUFFER
                case PUSH_STR: {
                                    std::cout << "[PUSH_STR]: value = " << ip->ristr << "\n";
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
                    std::cout << "[PUSH_INT]: value = " << ip->ri16 << "\n";
                    stackVM.push(ip->ri16);
                    ++ip;
                    break;


                // CMP_INT+LT N N N
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
                                   std::cout << "[COMPARE_INT_LT]: value = ";
                                   int16_t ans = (stackVM.pop()  > stackVM.pop())? 1 : 0;
                                   std::cout << ans << "\n";
                                   stackVM.push(ans);
                                   ++ip;
                                   break;
                                 }


                // LOAD_INT WILL BRING TO THE TOP OF THE STACK THE VARIABLE
                // WITH THE NAME OF THE TEMPORARY BUFFER
                case LOAD_INT:{
                                std::cout << "[LOAD INT]: value = " << stackVM.loadAt(stackVM.buffer_value) << "\n";
                                stackVM.push(stackVM.loadAt(stackVM.buffer_value));
                                ++ip;
                                break;
                              }


                // STORE_INT WILL STORE THE VARIABLE OF INTEGER TYPE WIDTH THE
                // NAME IN THE TEMPORARY BUFFER INSIDE THE STACK HASH MAP
                case STORE_INT: {
                                  std::cout << "[STORE INT]: value = " << stackVM.last() << "\n";
                                  stackVM.storeAt(ip->ristr, stackVM.pop());
                                  ++ip;
                                  break;                              
                                }
                

                // JMP_BY_IF_ZERO N N jumpLength
                // WILL JUMP jumpLength EVERYTIME STACK HAS VALUE OF 1 THAT
                // MEANS TRUE
                case JMP_BY_IF_ZERO: {
                                       std::cout << "[IF]: [CASE] = ";
                                       if (stackVM.pop() == 0) {
                                           ip += ip->ri16;
                                           std::cout << "FALSE\n";
                                       } else {
                                           ++ip;
                                           std::cout << "TRUE\n";
                                       }
                                       break;
                                     }


                // JMP_BACK N jumpLength
                // WILL JUMP BACK ALWAYS jumpLength STEPS
                case JMP_BACK: {
                                 std::cout << "[JUMP_BACK]:= value = " << ip->ri16 << "\n";
                                 ip -= ip->ri16;
                                 break;
                               }


                // USAGE FOR ENUM HOW MUCH INSTRUCTION THIS HAS
                case NUM_INSTRUCTION:
                                break;

            }
        }
        delete(ip);
        return 0;

    }
}
#endif /* ifndef INSTRUCTIONS */
