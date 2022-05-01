#include "../cpu/interpreter/Instruction.cpp"

int main(void)
{
    // CODE
    // PRINT FOO
    // PRINT BAR
    // 69+420 <- PRINT 
    // PRINT HELLLO WORLD

    Instruction myCode[] = {
        // LOAD FOO TO BUFFER
        Instruction{PUSH_STR, 0, 69, "FOO"},
        Instruction{PRINT_STR   , 0,    0},
        // PRINT BUFFER
        // LOAD BAR TO BUFFER
        Instruction{PUSH_STR, 0, 69, "BAR"},
        Instruction{PRINT_STR   , 0,    0},
        // PRINT BUFFER
        // LOAD 69 TO STACK
        Instruction{PUSH_INT, 0, 69},
        // LOAD 420 TO STACK
        Instruction{PUSH_INT, 0, 420},
        // CONCATENATE THE SUM TO STACK
        Instruction{ADD_INT, 0,0},
        // PRINT STACK BUFFER
        Instruction{PRINT_INT, 0, 0},
        // LOAD "Hello World" TO BUFFER
        Instruction{PUSH_STR, 0, 0, "Hello world"},
        // PRINT BUFFER
        Instruction{PRINT_STR, 0, 0},
        // EXIT WITH CODE 69
        Instruction{EXIT        , 0,    69}
    };
    testVM::run(myCode);
    return 0;
}
