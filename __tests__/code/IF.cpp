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
        Instruction{PUSH_STR,   0,  0,  "May i UwU you?\n"},    // buf -> <...>
        Instruction{PRINT_STR},                                 // stdout uwu :3

        Instruction{PUSH_STR,   0,  0,  "If x<10\n"},
        Instruction{PRINT_STR},

        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{PUSH_INT,   0,  6},          // value of x
        Instruction{STORE_INT},                 // int x = 6

        Instruction{PUSH_STR,   0,  0,  "x = "},
        Instruction{PRINT_STR},
        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{LOAD_INT},
        Instruction{PUSH_INT,   0,  5},
        Instruction{CMP_INT_LT},                // x < 5 
        Instruction{PRINT_INT},

        Instruction{JMP_BY_IF_ZERO, 0,  3},     // if x < 5

        Instruction{PUSH_STR,   0,  0,  "X is less than 5\n"},
        Instruction{PRINT_STR},


        Instruction{PUSH_STR,   0,  0,  "X is bigger than 5\n"},
        Instruction{PRINT_STR},
        Instruction{PUSH_STR,   0,  0,  "End of the program\n"},
        Instruction{PRINT_STR},
        Instruction{EXIT},

        

        
   };
    testVM::run(myCode);
    return 0;
}
