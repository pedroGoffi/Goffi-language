/*  NOTE:
 *      A tokenList is a vector of Atoms
 *      tokenList ==>  vec 
 *                      |   
 *                    Atom
 *                  /   |  \
 *              name  index type
 */


#ifndef LEXER
#define LEXER value

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include "./Core/Instructions.cpp"
#include "../frontend/Tools.cpp"
#include "../frontend/StringView.cpp"

/*  NOTE:
 *      A atom is a identifier for each word
 *      name is the name itself
 *      type is str/int types likely
 *      and index is the positio in the text
 */
class Atom{
public:
    std::string atomName;
    std::string atomType;
    uint64_t      atomIndex;
    uint64_t      atomIndexLine;
    uint64_t      atomLinkedIndex;
};
typedef enum Token_Type{
    NUMBER,
    BINARY_OPERAND,
    STRING,
    NAME
} Token_Type;
typedef struct Token{
    Token_Type       type;
    Atom             head;
} Token;

namespace Lexer{
    std::string Token_Type_To_String(Token_Type tk){
	switch(tk){
	    case NAME:
		return "Identifier";
		break;
	    case STRING: 
		return "String";
		break;
	    case BINARY_OPERAND: 
		return "BINARY_OPERAND";
		break;
	    case NUMBER:
		return "Number";
		break;
	    default:
		assert(false && "Unreachable");
	}
    }
    std::string Tokenize(std::string word, Token_Type &op){
	if (word == "\""){
	    std::cout << "OK\n";
	    exit(1);
	} else if( is_number(word)){
            op = NUMBER;
            return ("NUMERICAL_TYPE");
        } else if (word == "+"){
            op = BINARY_OPERAND;
            return ("OP_PLUS");
        } else if (word == "-"){
            op = BINARY_OPERAND;
            return ("OP_MINUS");
        } else if (word == "*"){
	    op = BINARY_OPERAND;
	    return ("OP_MULT");
	} else if (word == "<"){
            op = BINARY_OPERAND;
            return ("OP_CMP_LT");
        } else if (word == ">"){
            op = BINARY_OPERAND;
            return ("OP_CMP_GT");
        } else{
            op = NAME;
            return ("NAME_TYPE");
        }
    }
    void lex_line(std::vector<Token> &tokenVector, std::string source, uint64_t line){
        SV::stringView src = SV::SV(source);
        uint64_t  start = src.count;
        uint64_t  pos{};
        Token_Type           actualType;
        std::string          actualWord;
        std::string          token;
        std::vector<Token>   tokenList;
        while(src.count > src.minimunValue){
            actualWord = SV::separateByTokens(src);
	    if (actualWord.length() ==  0 ) continue;
            pos = start - src.count;
            token = Lexer::Tokenize(actualWord, actualType);
	    {
		tokenList.push_back(
            	    Token{
            	        .type = actualType,
            	        .head = Atom{
            	            actualWord, 
            	            token, 
            	            pos - actualWord.length(),
            	            line,
            	            0
            	        },
            	    }
            	);
	    }
        }
        for(auto& token_after_lex : tokenList)
            tokenVector.push_back(token_after_lex);
    }
    auto lex(std::fstream& file) -> std::vector<Token>
    {
	std::vector<Token> tokens_result;
	std::string line_string;
	uint64_t    line_count = 0;
	while( getline(file, line_string)){
	    Lexer::lex_line(tokens_result, line_string, line_count);
	    ++line_count;
	}
	file.close();
	return tokens_result;
    }
}


#endif /* ifndef LEXER */
