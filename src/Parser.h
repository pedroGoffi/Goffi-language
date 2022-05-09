#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE
#define ptr
#define token_usage


#include "./../cpu/interpreter/Instruction.cpp"
#include "./../cpu/interpreter/Compiler.cpp"

#include "./../includes/stdGoffi.cpp"
#include "./../includes/stdNum.cpp"
#include "./Lexer.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#define pushStack(op, r8, r16, rstr)   this->code.push_back(Instruction{op, r8, r16, rstr})
typedef enum : uint8_t{
    INT
} var_type;
typedef enum : uint8_t{
    OP_EXIT,               // exit N EXITCODE N
    OP_PANIC,              // PANIC N N N
    OP_ADD_INT,            // ADD N N N
    OP_SUB_INT,
    OP_DIV_INT,
    OP_MULT_INT,
    OP_PUSH_INT,           // PUSH_INT N value N
    OP_PUSH_STR,           // PUSH_STR N N string
    OP_PRINT_STR,          // PRINT_STR N N N
    OP_PRINT_INT,          // PRINT_INT N N N
    OP_CMP_INT_LT,         // CMP_INT_LT N N N
    OP_CMP_INT_GT,         // CMP_INT_GT
    OP_CMP_INT_EQU,        // CMP_INT_EQU
    OP_CMP_INT_LTE,        // CMP_INT_LTE
    OP_CMP_INT_GTE,        // CMP_INT_GTE
    OP_LOAD_INT,           // LOAD_INT N N N
    OP_STORE_INT,          // STORE_INT N N N
    OP_JMP_BY_IF_ZERO,     // JMP_BY_IF_ZERO N  jumpLength N
    OP_JMP_BACK,           // JMP_BACK N N N
    OP_DISPLAY,            // DISPLAY N N N
    OP_NUM_INSTRUCTION     // NUM_INSTRUCTION N N N

} op_type;

typedef enum{
    IF
} expr_type;
class Parser{
    tokenList                   tkvec;
    ptrType                     index;
    std::vector<Instruction>    code;
public:
    Parser(tokenList, ptrType&, int);
    ~Parser();
    void eval_expr(expr_type);
    void eval_op(op_type, tokenName);
    void eval(tokenPair);
};

#endif /* ifndef PARSER_HEADER_FILE */
