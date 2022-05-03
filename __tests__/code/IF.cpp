#include "../../cpu/interpreter/Instruction.cpp"

// store var
//  put char on buffer
//  put value in ri16
//  store as <char, ri16>
// on load
//  put char on buffer
//  put load then the last element on the stack
//      shall be the x value

int main(void)
{
    Instruction myCode[] = {
        Instruction{PUSH_STR,   0,  0,  "May i UwU you?"},  // buf -> <...>
        Instruction{PRINT_STR},                             // stdout uwu :3

        Instruction{PUSH_STR,   0,  0,  "x"},   // buf -> x
        Instruction{PUSH_INT,   0,  69},
        Instruction{PRINT_INT},
        Instruction{STORE_INT},

        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{LOAD_INT},
        Instruction{PRINT_STR},
        Instruction{EXIT},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},
        Instruction{},

        

        
   };
    testVM::run(myCode);
    return 0;
}
