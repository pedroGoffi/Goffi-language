
#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include "../atom/stack.cpp"
#include <cstdint>
#include <iostream>
#include <string>

enum OpCode: uint8_t {
    EXIT,
    ADD_INT,
    PUSH_INT,
    PUSH_STR,
    PRINT_STR,
    PRINT_INT,
    CMP_INT_LT,         // compare int less than
    LOAD_INT,
    STORE_INT,
    JMP_BY_IF_ZERO,     // jump some instructions
    JMP_BACK,           // jump back everytime
    DISPLAY,
    NUM_INSTRUCTION
};
class Instruction
{
    public:
        OpCode op_code;
        uint8_t  ri8; // primary   interpreted register
        uint16_t ri16; // secondary interpreted register
        std::string ristr; // register interpreted for string

};
namespace testVM{
    std::string VMVersion = "1.0";
    std::string author = "Pedro Henrique goffi de paulo";
    int run(Instruction code[])
    {
        std::cout 
            << "This VM is been developed by "
            << testVM::author
            << "\nVersion: "
            << testVM::VMVersion 
            << "\n";
        class stack<int16_t> stackVM(1024);
        Instruction *ip = code;

        while(ip != nullptr)
        {
            switch(ip->op_code)
            {
                case DISPLAY:
                    while(1){
                        std::cout << stackVM.pop() << ", ";
                        break;
                    }
                case EXIT:
                    exit(ip->ri16);
                    ip = nullptr;
                    break;
                case PRINT_INT:{                                
                                 std::cout <<"[PRINT]: value = "<< stackVM.last() << "\n";
                                 ++ip;
                                 break;
                               }

                case ADD_INT:{
                                std::cout << "[ADD_INT]: value = ";
                                int16_t RHS = stackVM.pop();
                                stackVM.push(stackVM.pop()+RHS);
                                std::cout << stackVM.last() << "\n";
                                ++ip;                            
                                break;
                             }

                case PUSH_STR: {
                                  std::cout << "[PUSH_STR]: value = " << ip->ristr << "\n";
                                  stackVM.buffer(ip->ristr);
                                  ++ip;
                                  break;
                                }

                case PRINT_STR: {  
                                  std::cout << "[PRINT]: value = " << stackVM.buffer_value << "\n";
                                  //std::cout << stackVM.buffer_value;
                                  ++ip;
                                  break;
                                }

                case PUSH_INT:
                    std::cout << "[PUSH_INT]: value = " << ip->ri16 << "\n";
                    stackVM.push(ip->ri16);
                    ++ip;
                    break;

                case CMP_INT_LT: {
                                   std::cout << "[COMPARE_INT_LT]: value = ";
                                   int16_t ans = (stackVM.pop()  > stackVM.pop())? 1 : 0;
                                   std::cout << ans << "\n";
                                   stackVM.push(ans);
                                   ++ip;
                                   break;
                                 }

                case LOAD_INT:{
                                std::cout << "[LOAD INT]: value = " << stackVM.loadAt(stackVM.buffer_value) << "\n";
                                stackVM.push(stackVM.loadAt(stackVM.buffer_value));
                                ++ip;
                                break;
                              }

                case STORE_INT: {
                                  std::cout << "[STORE INT]: value = " << stackVM.last() << "\n";
                                  std::cout << "name | value " << ip->ristr << stackVM.last() << "\n";
                                  stackVM.storeAt(ip->ristr, stackVM.pop());
                                  ++ip;
                                  break;
                                }
                
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
                case JMP_BACK: {
                                 std::cout << "[JUMP_BACK]:= value = " << ip->ri16 << "\n";
                                 ip -= ip->ri16;
                                 break;
                               }

                case NUM_INSTRUCTION:
                                break;
            }
        }
        delete (ip);
        return 0;

    }
}
#endif /* ifndef INSTRUCTIONS */
