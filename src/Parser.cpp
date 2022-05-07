#ifndef PARSER_CPP
#define PARSER_CPP 
#include <fstream>
#include "./Lexer.cpp"
#define debug_parser(word, type)        std::cout<<"[PARSER][WORD-PARSED] :\t"<<word<<"\t[TYPE] :\t"<<type<<"\n"

namespace Parser{
    void compile_to_bytecode(tokenList tkvec, ptrType& idx){
        /*
         *  -- OP VAR1 VAR2 VAR3 
         *  Example 
         *  -- PUSH_STR 0   0   "Hello world"
         *  -- PRINT_STR         
         */
        for(auto& vec : tkvec){
            debug_parser(vec.first, vec.second);
            incPtr(idx);
        }
    }
}
int main(void)
{
    /*  NOTE
     *      When lex lex string literal
     *      stmt -> "{" -> stmt -> "}" -> x
     *      stmt -> optional (op_type_identifier -> "(" -> expr -> ")") -> stmt
     */
    loadPtr(current_index, 0);
    tokenList _token_vector;
    std::string src = 
        "   1 2 + print"
    ;
    Lexer::run(src, current_index, _token_vector);
    resetPtr(current_index);
    Parser::compile_to_bytecode(_token_vector, current_index);
    return 0;
}
#endif /* ifndef PARSER_CPP */
