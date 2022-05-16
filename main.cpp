#ifndef MAIN
#define MAIN 

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#define T_IMPLS
#include "./src/Tools.h"
#include "./src/goffi.cpp"
#include "./src/Lexer.cpp"
#include "./src/Parser.cpp"

#define SHIFT shift(&argc, &argv)

int main(int argc, char** argv){
    std::string const program         = SHIFT;
    std::string inputFilePath;
    std::string outputFilePath        = "out.gf";
    std::string flag;
    bool        simulate;
    bool        compile;
    while(argc > 0){
        flag = SHIFT;

        if(flag == "-o"){
            if (argc <= 0){
                usage(stderr, program);
                fprintf(stderr, "Error: Flag -o has no uwu");
            }
            outputFilePath = SHIFT;
        }
        else if (flag == "-h"){
            usage(stdout, program);
            exit(0);
        }
        else if (flag == "com"){
            compile  = true;
            simulate = false;
        }
        else if (flag == "sim"){
            simulate = true;
            compile  = false;
        }
        else{
            inputFilePath = flag;
        }
    }
    if(inputFilePath.length()  == 0){
        usage(stderr, program);
        fprintf(stderr, "Error: No input file path was provided\n");
        exit(1);
    }
    std::fstream INPUT_FILE(inputFilePath, std::ios::in);
    assert(INPUT_FILE.is_open() && "Error: Could not open the file\n");
    std::string code;
    std::string line;
    std::vector<Token>  tokens;
    size_t lineCount = 1;
    while(getline(INPUT_FILE, line)){
        Lexer::lex_line(tokens, line, lineCount);
        ++lineCount;
    }
    INPUT_FILE.close();

    if(simulate){
        Crossreference::simulation_mode(tokens);
        std::vector<VR>     instructions = Parser::parse(tokens);
        Goffi::simulate_program(instructions);
    }
    else if (compile){
        std::vector<VR>     instructions = Parser::parse(tokens);
        Crossreference::compilation_mode(instructions);
        Goffi::compile_program(instructions, outputFilePath);
    }
    else{
        usage(stderr, program);
        fprintf(stderr, "Error: You must specify if you want simulation mode of compilation  mode\n");
        exit(1);
    }
    return 0;

}
#endif /* ifndef MAIN */
