#ifndef PARSER_CPP
#define PARSER_CPP 
#define ptr
#define token_usage
#include "./Parser.h"
Parser::~Parser(){}

argType Parser::eval_args(int MAX_ARGS){
    /*  NOTE:
     *      argType is a pair of an integer that stands for how much arguments
     *      the expression has and a vector that stands for the inside
     *      arguments
     *          Acess:
     *              first   == arg_count
     *              second  == arg_values
     */
    int                     arg_count = 1;
    std::vector<tokenPair>  arg_values(MAX_ARGS);
    incPtr(this->index);
    gassert(
        this->tkvec[*this->index].second == "OPEN_CIRCULAR_BRACKETS",
        "Argument blocks are only open with CIRCULAR BRACKETS, AKA: `(`"
    );
    incPtr(this->index);
    for(;this->tkvec[*this->index].second != "CLOSE_CIRCULAR_BRACKETS";){
        /*  TODO:
         *      Take the args and put inside arg_values
         */
        arg_values.push_back(this->tkvec[*this->index]);
        if(this->tkvec[*this->index].second == "COMMA")
            ++arg_count;
        incPtr(this->index);
    }
    incPtr(this->index);
    return std::pair<int, std::vector<tokenPair>>(arg_count, arg_values);
}
void Parser::eval_expr(expr_type expr){
    (void) expr;
    switch(expr){
        case IF:
            while (this->tkvec[*this->index].first != "do"){
                /*  TODO:
                 *      A linked list to specify where it starts and where it
                 *      ends
                 */

                incPtr(this->index);
                this->eval(this->tkvec[*this->index]);
            }
            break;
    }
}
void Parser::eval_op(op_type op, tokenName value){
    switch(op){
        case OP_PUSH_INT:
            pushStack(PUSH_INT, 0,  parseSTRtoUINT8_T(value), "");
            break;
            
        case OP_PUSH_STR:
            pushStack(PUSH_STR, 0,  0,  value);
            break;

        case OP_EXIT: {
            //std::shared_ptr<argType> args = std::make_shared<argType>(this->eval_args());
            // 1 padding
            std::shared_ptr<argType> args = std::make_shared<argType>(this->eval_args(1));
            gassert(
                args->first == 1, 
                "Exit function only handle one argument, the exit call"
            );
            pushStack(EXIT, 0, parseSTRtoUINT8_T(args->second[1].first), "");
            break;
        }
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
            pushStack(CMP_INT_GT,   0,  0,  "");
            break;
            
        case OP_CMP_INT_EQU:
            pushStack(CMP_INT_EQU,   0,  0,  "");
            break;

        case OP_CMP_INT_LTE:
            pushStack(CMP_INT_LTE,   0,  0,  "");
            break;

        case OP_CMP_INT_GTE:
            pushStack(CMP_INT_GTE,   0,  0,  "");
            break;

        case OP_LOAD_INT:
            pushStack(LOAD_INT,   0,  0,  "");
            break;

        case OP_STORE_INT:
            pushStack(STORE_INT,   0,  0,  "");
            break;

        case OP_JMP_BY_IF_ZERO:
            pushStack(CMP_INT_GT,   0,  0,  "");
            break;

        case OP_JMP_BACK:
            pushStack(JMP_BACK, 0,  parseSTRtoUINT8_T(value), "");
            break;
        case OP_DISPLAY:
            pushStack(DISPLAY,   0,  0, "");
            break;

        case OP_NUM_INSTRUCTION:                        
            pushStack(EXIT, 0,  0, "");
            break;
    }
}

Parser::Parser(
        tokenList tkvec, 
        ptrType& idx,
        int howContinueAfterParsing
    ){
    resetPtr(idx);
    this->index = idx;
    this->tkvec = tkvec;
    unsigned int MAX_LEN = tkvec.size();
    for(;*this->index < MAX_LEN;){
        this->eval(this->tkvec[*this->index]);
        incPtr(this->index);
    }
    pushStack(EXIT, 0,  0,  "");
    switch(howContinueAfterParsing){
        /*  CASE 1 THIS WILL SIMULATE THE PROGRAM */
        case 1:
            testVM::run(this->code);
            break;

        /*  CASE 2 THIS WILL COMPILE THE PROGRAM TO ASSEMBLY */
        case 2:
            testVM::compile_asm(this->code);
            break;
    }
}
void Parser::eval(tokenPair op){
    debug_parser(op.first, op.second);

    if      (op.second == "INT")                    this->eval_op(OP_PUSH_INT,       op.first);     
    else if (op.second == "STRING_LITERAL")         this->eval_op(OP_PUSH_STR,       op.first);

    else if (op.second == "CMP_LT")                 this->eval_op(OP_CMP_INT_LT,     op.first);
    else if (op.second == "OP_PLUS")                this->eval_op(OP_ADD_INT,        op.first);
    else if (op.second == "OP_SUB")                 this->eval_op(OP_SUB_INT,        op.first);
    else if (op.second == "OP_DIV")                 this->eval_op(OP_DIV_INT,        op.first);
    else if (op.second == "OP_MULT")                this->eval_op(OP_MULT_INT,       op.first);
    else if (op.second == "__EOF__")                this->eval_op(OP_EXIT,           op.first);



    else if (op.first  == "puts" )                  this->eval_op(OP_PRINT_INT,      op.first);

    else if (op.first  == "do" )                    this->eval_op(OP_JMP_BY_IF_ZERO, op.first);
    else if (op.first  == "end")                     std::cout << "TODO JUMP BACK\n";
    else if (op.first  == "if")                     this->eval_expr(IF);
    else if (op.first  == "panic" )                 this->eval_op(OP_PANIC,          op.first);
    else if (op.first  == "print" )                 this->eval_op(OP_PRINT_STR,      op.first);
    else if (op.first  == "exit")                   this->eval_op(OP_EXIT,           op.first);
    else if (op.first  == "__stack__")              this->eval_op(OP_DISPLAY,        op.first);
    else if (op.first  == "\"")                     return;
    else{
        /*  UNREACHABLE */
        char err_log[128];
        sprintf(err_log, "Unreachable OP_TYPe, or Native Function call at (%s), at the index (%d)", 
                tkvec[*this->index].first.c_str(),
                *this->index
        );
        gassert(false, err_log);
    }
}
#endif /* ifndef PARSER_CPP */
