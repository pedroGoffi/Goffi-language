#include "../../cpu/interpreter/Instruction.cpp"


int main(void)
{
    // for (int x = 1; x < 10; x++) 
    //  PRINT X
    //  
    Instruction myCode[] = {
        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{PUSH_INT,   0,  0},     // x = 0
        Instruction{STORE_INT},

        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{LOAD_INT},
        Instruction{PUSH_INT,   0,  10},
        Instruction{CMP_INT_LT},

        Instruction{JMP_BY_IF_ZERO, 0,  12},
        // {
            Instruction{PUSH_STR,   0,  0,  "x"},
            Instruction{LOAD_INT},
            Instruction{PUSH_INT,   0,  1},
            Instruction{ADD_INT},

            Instruction{STORE_INT},

            Instruction{PUSH_STR,   0,  0,  "x = "},    // print after (x+=1)
            Instruction{PRINT_STR},
            Instruction{PUSH_STR,   0,  0,  "x"},
            Instruction{LOAD_INT},

            Instruction{PRINT_INT},
        // }
        Instruction{JMP_BACK,   0,  16},

        Instruction{PUSH_STR,   0,  0,  "-- fim do programa --\n"},
        Instruction{PRINT_STR},

        Instruction{EXIT,   0,  0}
   };
    testVM::run(myCode);
    return 0;
}
