#ifndef PARSER_CPP
#define PARSER_CPP 
#define ptr
#define token_usage
#include "./Parser.h"

Parser::~Parser(){}
void Parser::eval_expr(expr_type expr, tokenList Node){
    (void) expr;
    (void) Node;
}
void Parser::eval_op(op_type op){
    (void) op;
}
void Parser::eval(op_type op, tokenName value){
    switch(op){
        case OP_PUSH_INT:
            pushStack(PUSH_INT, 0,  static_cast<uint16_t>(std::stoi(value)), "");
            break;
        case OP_PUSH_STR:
            pushStack(PUSH_STR, 0,  0,  value);
            break;

        case OP_EXIT:            
            pushStack(EXIT, 0, 0, "");
            break;
        case OP_PANIC:
            pushStack(PANIC, 0, 0, "");
            break;
        case OP_ADD_INT:
            pushStack(ADD_INT, 0,  0, "");
            break;

        case OP_SUB_INT:
            pushStack(SUB_INT,  0,  0,  "");
            break;

        case OP_DIV_INT:
            pushStack(DIV_INT,  0,  0,  "");
            break;

        case OP_MULT_INT:
            pushStack(MULT_INT, 0,  0,  "");
            break;


        case OP_PRINT_STR:
            pushStack(PRINT_STR, 0, 0, "");
            break;

        case OP_PRINT_INT:
            pushStack(PRINT_INT,    0,  0,  "");
            break;

        case OP_CMP_INT_LT:
            break;

        case OP_CMP_INT_GT:
            break;
            
        case OP_CMP_INT_EQU:
            break;

        case OP_CMP_INT_LTE:
            break;

        case OP_CMP_INT_GTE:
            break;

        case OP_LOAD_INT:
            break;

        case OP_STORE_INT:
            break;

        case OP_JMP_BY_IF_ZERO:
            break;

        case OP_JMP_BACK:
            pushStack(JMP_BACK, 0,  static_cast<uint8_t>(std::stoi(value)), "");
            break;
        case OP_DISPLAY:
            pushStack(DISPLAY,   0,  0, "");
            break;

        case OP_NUM_INSTRUCTION:                        
            pushStack(EXIT, 0,  0, "");
            break;
    }
}
Parser::Parser(tokenList tkvec, ptrType& idx){    
    this->index = 0;    
    for(auto& v : tkvec){
        /*  TODO:   
         *      In puts parse the data type for diferent types of printing
         */
        debug_parser(v.first, v.second);

        if      (v.second == "INT")             this->eval(OP_PUSH_INT,     v.first);        
        else if (v.second == "STRING_LITERAL")  this->eval(OP_PUSH_STR,     v.first);
        else if (v.second == "OP_PLUS")         this->eval(OP_ADD_INT,      v.first);
        else if (v.second == "OP_SUB")          this->eval(OP_SUB_INT,      v.first);
        else if (v.second == "OP_DIV")          this->eval(OP_DIV_INT,      v.first);
        else if (v.second == "OP_MULT")         this->eval(OP_MULT_INT,     v.first);
        else if (v.second == "__EOF__")         this->eval(OP_EXIT,         v.first);

        else if (v.first  == "puts" )           this->eval(OP_PRINT_INT,    v.first);
        else if (v.first  == "print" )          this->eval(OP_PRINT_STR,    v.first);
        else if (v.first  == "exit")            this->eval(OP_EXIT,         v.first);
        else if (v.first  == "__stack__")       this->eval(OP_DISPLAY,      v.first);

        ++this->index;
    }
    
    debug_parser("[START CODE RUNTIME]","");
    testVM::run(this->code);
}
#endif /* ifndef PARSER_CPP */
