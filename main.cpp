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
void std_in(){
        std::string         INPUT;
        std::vector<Token>  tokenStdin;
        std::vector<VR>     Instructions;
        while(1){
            fprintf(stdout, "Gff-Stdin>  ");
            std::getline(std::cin >> std::ws, INPUT);
            Lexer::lex_line(tokenStdin, INPUT, 0);
            Crossreference::simulation_mode(tokenStdin);
            Instructions = Parser::parse(tokenStdin);
            Goffi::simulate_program(Instructions);    
            fprintf(stdout, "\n");
        }
        exit(0);

}
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
    if(simulate || compile){
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
    }
    else
        std_in();
    return 0;

}
#endif /* ifndef MAIN */
