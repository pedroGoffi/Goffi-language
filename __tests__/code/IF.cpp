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
        // Entry point
        Instruction{PUSH_STR,   0,  0,  "Hello world"}, // tmp_buffer = Hello world
        Instruction{PRINT_STR,   0,  0,  0},            // print tmp_buffer 
        // ------------------------------------------
        //Instruction{PUSH_STR,   0,  0,  "x"},       // tmp_buffer = x
        //Instruction{PUSH_INT,   0,  69},            // 69
        //Instruction{STORE_INT},                     // <remove from stack, and store>(X = 69)
        
        //Instruction{PUSH_STR,   0,  0,  "x"},       // tmp_buffer = x
        //Instruction{LOAD_INT},                      // call hash(tmp_buffer)
        
        //Instruction{PUSH_STR,   0,   0,  "x"},      // tmp_buffer = x
        //Instruction{LOAD_INT},                      // throw (x -> stack)
        //Instruction{PUSH_INT,   0,  10},            // x 10
        //Instruction{CMP_INT_LT},                    // (!(x 10 <) -- x < 10) throw if true (1) else (0)
        
        

        
        //Instruction{PUSH_STR,   0,  0,  "x"},       // tmp_buffer = x
        //Instruction{LOAD_INT},                      // call hash(tmp_buffer)
        //Instruction{PUSH_INT,   0,  69},
        //Instruction{ADD_INT},
        
        //Instruction{PRINT_STR},
        Instruction{EXIT},

        

        
   };
    testVM::run(myCode);
    return 0;
}
