#include "../../cpu/interpreter/Instruction.cpp"


int main(void)
{
    // for (int x = 1; x < 10; x++) 
    //  PRINT X
    //  
    Instruction myCode[] = {
	Instruction{PUSH_STR,	0,	0,	"Something went wrong\n"},
        Instruction{PANIC,	0,	__LINE__},
        Instruction{EXIT,   0,  0}
   };
    testVM::run(myCode);
    return 0;
}
