// this shall use stack to run simple program
//  Instruc(print 1+1)


#define  OPEN_FILE
#include "./includes/stdGoffi.h"
#include "./src/Parser.cpp"
#include <cassert>


int main(int argc, char** argv)
{
    // accept flags to open a file

    char* filePath = argv[1];
    // TODO: try logic
    // open the file
    std::fstream file(filePath, std::ios::in);
    assert(file.is_open() && "[Error]: Could not open the file");
    parser::parse(file);
    /*  TODO
     *      After parsing use compile(com) bytecode(byte) or simulate (sim)
     *      for further code
     */
    return 0;
}
