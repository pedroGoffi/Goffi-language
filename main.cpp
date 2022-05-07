// this shall use stack to run simple program
//  Instruc(print 1+1)

#ifndef MAIN_GOFFI_LANGUAGE
#define MAIN_GOFFI_LANGUAGE

#include "./src/Parser.cpp"
#include "./src/Lexer.cpp"
#include <iostream>
#include <string>
#include <fstream>


#define eat_file(file, line) while( getline(file, line) )

int main(int argc, char* argv[])
{    
    bool compile_byte_code;
    bool compile_to_nativecode;

    std::string target_file;
    for (int i = 0; i < argc; ++i) {
        if      (argv[i] == std::string("byte")){
            compile_byte_code = true;
        }
        else if (argv[i] == std::string("com")){
            compile_to_nativecode = true;
        }
        else{
            target_file = argv[i];
        }
    }
    initTmp(src);
    initTmp(line);
    std::ifstream file(target_file, std::ios::in);

    /*  TODO: assertions */
    //assert(compile_byte_code || compile_to_nativecode);
    eat_file(file, line) src += line;
    
    tokenList token_vector;
    loadPtr(index, 0);
    Lexer::run(src, index, token_vector);
    resetPtr(index);
    if(compile_byte_code){
        Parser::compile_to_bytecode(token_vector, index);

    }
    if(compile_to_nativecode){
        Parser::compile_to_nativecode(token_vector, index);
    }
    return 0;
}
#endif /* ifndef MAIN_GOFFI_LANGUAGE */
