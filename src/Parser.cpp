#ifndef PARSER_CPP
#define PARSER_CPP 
#define ptr
#define token_usage
#include "./Parser.h"

Parser::~Parser(){}
void Parser::eval_expr(expr_type expr, tokenList Node){
    (void) expr;
    (void) Node;
    switch(expr){
        case IF:
            /*  TODO */
            break;
    }
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
            pushStack(CMP_INT_LT,   0,  0,  "");
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

    resetPtr(idx);
    unsigned int MAX_LEN = tkvec.size();
    for(; *idx < MAX_LEN ;){
        debug_parser(tkvec[index].first, tkvec[index].second);
        if      (tkvec[*idx].second == "INT")             this->eval(OP_PUSH_INT,       tkvec[*idx].first);     
        else if (tkvec[*idx].second == "STRING_LITERAL")  this->eval(OP_PUSH_STR,       tkvec[*idx].first);

        else if (tkvec[*idx].second == "CMP_LT")          this->eval(OP_CMP_INT_LT,     tkvec[*idx].first);
        else if (tkvec[*idx].second == "OP_PLUS")         this->eval(OP_ADD_INT,        tkvec[*idx].first);
        else if (tkvec[*idx].second == "OP_SUB")          this->eval(OP_SUB_INT,        tkvec[*idx].first);
        else if (tkvec[*idx].second == "OP_DIV")          this->eval(OP_DIV_INT,        tkvec[*idx].first);
        else if (tkvec[*idx].second == "OP_MULT")         this->eval(OP_MULT_INT,       tkvec[*idx].first);
        else if (tkvec[*idx].second == "__EOF__")         this->eval(OP_EXIT,           tkvec[*idx].first);


        else if (tkvec[*idx].first  == "puts" )           this->eval(OP_PRINT_INT,      tkvec[*idx].first);
        else if (tkvec[*idx].first  == "if")              this->eval_expr(IF,           tkvec);
        else if (tkvec[*idx].first  == "panic" )          this->eval(OP_PANIC,          tkvec[*idx].first);
        else if (tkvec[*idx].first  == "print" )          this->eval(OP_PRINT_STR,      tkvec[*idx].first);
        else if (tkvec[*idx].first  == "exit")            this->eval(OP_EXIT,           tkvec[*idx].first);
        else if (tkvec[*idx].first  == "__stack__")       this->eval(OP_DISPLAY,        tkvec[*idx].first);
        else if (tkvec[*idx].first  == "\"")              continue;
        else{
            /*  UNREACHABLE */
            char err_log[128];
            sprintf(err_log, "Unreachable OP_TYPe, or Native Function call at (%s)", tkvec[index].first.c_str());
            gassert(false, err_log);
        }
        ++this->index;

    }
    
    debug_parser("[START CODE RUNTIME]","");
    testVM::run(this->code);
}
#endif /* ifndef PARSER_CPP */
