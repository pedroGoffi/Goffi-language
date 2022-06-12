#ifndef MAIN
#define MAIN 

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include "./frontend/Tools.h"
#include "./backend/goffi.cpp"
#include "./backend/Lexer.cpp"
#include "./backend/Parser.cpp"
#include "backend/goffi.h"

#define SHIFT shift(&argc, &argv)
void std_in(){
        std::string         INPUT;
        std::vector<Token>  tokenStdin;
        std::vector<VR>     Instructions;
        while(1){
            fprintf(stdout, "Gff-Stdin>  ");
	    
            std::getline(std::cin >> std::ws, INPUT);
            Lexer::lex_line(tokenStdin, INPUT, 0);
            Crossreference::analyze(tokenStdin);
            Instructions = Parser::parse(tokenStdin);
            Goffi::simulate_program(Instructions);    
	    
            fprintf(stdout, "\n");
	    tokenStdin = {};
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



        std::vector<Token>  tokens = Lexer::lex(INPUT_FILE);
        Crossreference::analyze(tokens);
        std::vector<VR>     instructions = Parser::parse(tokens);

	(compile == true)
	? Goffi::compile_program(instructions, outputFilePath)
	: Goffi::simulate_program(instructions);

    }
    else if (inputFilePath.length() == 0){
        std_in();
    } else {
	usage(stderr, program);
        fprintf(stderr, "Error: if filePath is provided you have use a flag to specify the mode, like: sim or com");
    }
    return 0;

}
#endif /* ifndef MAIN */
