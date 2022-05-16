#ifndef CORE_INSTRUCTIONS
#define CORE_INSTRUCTIONS 
#include <stdint.h>
typedef enum{
    PUSH_INT,
    OP_PLUS,
    OP_MINUS,
    OP_EQUALS,
    OP_GTHAN,
    OP_LTHAN,    
    OP_MEM,
    DUMP,
    DUP,
    EXIT,
    WHILE,
    OP_END,

    OP_IF,
    OP_DO,
    OP_ELSE,

    OP_LOADBYTE,
    OP_STOREBYTE,
    NUM_OF_OPERANDS        
} Op_type;

typedef struct{
    Op_type  op;
    uint64_t operand;
}VR;
#endif /* ifndef CORE_INSTRUCTIONS */
