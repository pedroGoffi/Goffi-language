#include "../../cpu/interpreter/Instruction.cpp"

int main(void)
{
    Instruction myCode[] = {
        Instruction{PUSH_STR, 0, 69, "FOO\n"},
        Instruction{PRINT_STR},
        Instruction{PUSH_STR, 0, 69, "BAR\n"},
        Instruction{PRINT_STR},
        Instruction{PUSH_INT, 0, 69},
        Instruction{PUSH_INT, 0, 420},
        Instruction{ADD_INT},
        Instruction{PRINT_INT},
        Instruction{PUSH_STR, 0, 0, "Hello world\n"},
        Instruction{PRINT_STR, 0, 0},
        Instruction{EXIT        , 0,    69}
    };
    testVM::run(myCode);
    return 0;
}
