#ifndef PARSER_CPP
#define PARSER_CPP 
#define ptr
#define token_usage

#include "./../includes/stdGoffi.cpp"
#include "./../includes/stdNum.cpp"
#include "./Lexer.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

/*  BYTECODE SPACE */
typedef enum {
    INT
} var_type;

typedef enum {
    PUTS
} op_type;
typedef enum {
    IF
} expr_type;

namespace Parser{
    void eval_expr(expr_type expr, tokenList Node){
        switch(expr){
            case IF:
                //if(expr){ statement }
                break;
        }
    }
    void eval_op(op_type op){
        switch(op){
            case PUTS:
                /*  TODO */
                break;
        }
    }
    void eval_int(int value){

        std::cout << "TODO: PUSH INTEGER TO STACK\n";
    }
    void compile_to_bytecode(tokenList tkvec, ptrType& idx){
        for(auto& chr:tkvec){
            if(gff::is_number(chr.first)){                
                Parser::eval_int(std::stoi(chr.first));                
            }
            else if (chr.first == "puts"){
                Parser::eval_op(PUTS);
            }
        }
    }
}

/*  NATIVE CODE SPACE */
namespace Parser {
    void compile_to_nativecode(tokenList tkvec, ptrType& idx){
        std::cout << "[TODO]\n";
        (void) tkvec;
        (void) idx;
        exit(69);
    }
}
#endif /* ifndef PARSER_CPP */
