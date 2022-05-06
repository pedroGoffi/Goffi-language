#ifndef PARSER_CPP
#define PARSER_CPP 
#include <fstream>
#include "./Lexer.cpp"
namespace parser{
    void parse(std::fstream& file){
        /*  TODO */
        Lexer::lex(file);
    }
};
#endif /* ifndef PARSER_CPP */
