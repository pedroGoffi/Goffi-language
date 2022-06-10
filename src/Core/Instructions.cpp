#ifndef CORE_INSTRUCTIONS
#define CORE_INSTRUCTIONS 
#include <stdint.h>
typedef enum{
    PUSH_INT,
    OP_PLUS,
    OP_MINUS,
    OP_EQUALS,
    OP_MULT,
    OP_GTHAN,
    OP_LTHAN,    
    OP_MEM,
    DUMP,
    DUP,
    DROP, 
    OVER, // a b -> a b a 
    SWAP, // a b -> b a
    ROT,// a b c -> c b a


    OP_IF,
    OP_WHILE,
    OP_DO,
    OP_END,



    OP_LOADBYTE,
    OP_STOREBYTE,
    NUM_OF_OPERANDS        
} Op_type;

typedef struct{
    Op_type  op;
    uint64_t operand;
}VR;
#endif /* ifndef CORE_INSTRUCTIONS */
