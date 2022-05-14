#ifndef GOFFI_SRC
#define GOFFI_SRC
#include "./Core/Instructions.cpp"
#include <iostream>
#include <vector>

namespace Goffi{
    void simulate_program(std::vector<VR> &program);
    void compile_program(std::vector<VR> program, std::string outputFilePath); 
}
#endif /* ifndef GOFFI_SRC */
