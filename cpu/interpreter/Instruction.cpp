#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include "../atom/stack.cpp"
#include <cstdint>
#include <iostream>

enum OpCode: uint8_t {
    EXIT,
    ADD_INT,
    PUSH_INT,
    PRINT_INT,
    NUM_INSTRUCTION
};
class Instruction
{
    public:
        OpCode op_code;
        uint8_t  ri8; // primary   interpreted register
        uint16_t ri16; // secondary interpreted register

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
        class stack<uint16_t> stackVM(1024);
        Instruction *ip = code;
        while(ip != nullptr)
        {
            switch(ip->op_code)
            {
                case EXIT:
                    ip = nullptr;
                    break;
                case PRINT_INT:{
                    std::cout << stackVM.last() << "\n";
                    ++ip;
                    break;
                }
                case ADD_INT:{
                    uint16_t RHS = stackVM.pop();
                    uint16_t LHS = stackVM.pop();
                    stackVM.push(LHS+RHS);
                    ++ip;
                    break;
                }
                case PUSH_INT:
                    stackVM.push(ip->ri16);
                    ++ip;
                    break;
                case NUM_INSTRUCTION:
                    break;
            }
        }
        delete (ip);
        return 0;

    }
}
#endif /* ifndef INSTRUCTIONS */
