#include "../cpu/interpreter/Instruction.cpp"
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
        Instruction{PUSH_STR,   0,  0,  "Iniciando programa\n"},
        Instruction{PRINT_STR,  0,  0},
        
        Instruction{PUSH_INT,   0,  2},
        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{STORE_INT},
           
        Instruction{PUSH_STR,   0,  0,  "x"},       
        
        Instruction{LOAD_INT},
        Instruction{PRINT_INT},
        
        Instruction{PUSH_INT,   0,  10},       
        Instruction{CMP_INT_LT},
        
        Instruction{JMP_BY_IF_ZERO, 0,  9},

        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{LOAD_INT},
        Instruction{PUSH_INT,   0,  5},
        Instruction{PRINT_INT},

        Instruction{PUSH_STR,   0,  0,  "x"},
        Instruction{STORE_INT},                                  
       
                                     
        Instruction{DISPLAY},
        Instruction{JMP_BACK,   0,  15},
               
        Instruction{PUSH_STR,   0,  0,  "FIM DO PROGRAMA"},
        Instruction{PRINT_STR,  0,  0},
        Instruction{EXIT},

        
    };
    testVM::run(myCode);
    return 0;
}
