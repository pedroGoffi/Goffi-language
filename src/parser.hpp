// -------------------
// not implemented yet
// -------------------

#ifndef PARSER_HPP
#define PARSER_HPP 

#include <fstream>
#include "../includes/stdGoffi.h"
namespace parser{
    std::string eat(std::fstream& file)
    {
        std::string code = "";
        {
            std::string line;
            while( std::getline(file, line) )
            {
                code += line;
            }
        }
        return code;
    }


    void parse(std::fstream& file){
        std::string code = parser::eat(file);
        std::cout << code << "\n";
        file.close();
    }


};
#endif /* ifndef PARSER_HPP */
