#include "../cpu/interpreter/Instruction.cpp"

int main(void)
{
    Instruction myCode[] = {
        Instruction{PUSH_INT    , 0,  420},
        Instruction{PUSH_INT    , 0,   69},
        Instruction{ADD_INT     , 0,    0},
        Instruction{PRINT_INT   , 0,    0},
        Instruction{EXIT        , 0,    1}
    };
    testVM::run(myCode);
    return 0;
}
