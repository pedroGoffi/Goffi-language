// this shall use stack to run simple program
//  Instruc(print 1+1)


#define  OPEN_FILE
#include "./includes/stdGoffi.h"
#include "./src/Parser.cpp"



int main(int argc, char** argv)
{
    // accept flags to open a file
    char* filePath = argv[1];
    // TODO: try logic
    // open the file
    std::fstream file(
        filePath, 
        std::ios::in
    );
    if(file.is_open() == false){
        gff::onError("Couldn't open the file");
    }
    parser::parse(file);

    return 0;
}
