/*  NOTE:
 *      A tokenList is a vector of Atoms
 *      tokenList ==>  vec 
 *                      |   
 *                    Atom
 *                  /   |  \
 *              name  index type
 */

#include <cstdint>
#ifndef LEXER
#define LEXER value

#include<iostream>
#include <vector>
#include <string>
#include "./Core/Instructions.cpp"
#include "./Tools.hpp"

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
typedef enum{
    NUMBER,
    BINARY_OPERAND,
    STRING
} Token_Type;
typedef struct Token_ast Token;
struct Token_ast{
    Token_Type       type;
    Atom             head;
};
/*  WT stands for word type */

std::string WT(char w){
    if (std::isalpha(w))        return "STR";
    else if (std::isdigit(w))   return "NUM";

    else if (w == '(')          return "LPAREN"; 
    else if (w == ')')          return "RPAREN";

    else if (w == '+')          return "PLUS";
    else if (w == '-')          return "MINUS";
    else if (w == '*')		return "MULT";

    return "__BlANK__";
}
namespace SV{
    uint64_t countChar(std::string src){
        uint64_t i = 0;
        uint64_t len = src.length();
        while(i <= len){
            i += 1;
        }
        return i;
    }
    typedef struct {
        uint64_t      count;
        std::string src;
        uint64_t      minimunValue = 1;
    }stringView;

    stringView SV(std::string src, uint64_t count = 0){
        stringView sv;
        sv.count = (count == 0) 
            ? SV::countChar(src)
            : count;
        sv.src   = src;
        return sv;
    }
    
    void trimLeft(SV::stringView &sv){

        uint64_t len = sv.src.length();
        uint64_t index = 0;

        while(index < len && isspace(sv.src[index])){
            ++index;
        }
        sv.count -= index;
        sv.src = sv.src.substr(index, sv.src.length());
    }
    std::string separateByTokens(SV::stringView &sv){
        SV::trimLeft(sv);
        uint64_t len = sv.src.length();
        uint64_t i = 0;
        std::string result;

        std::string thisTkName;
        std::string nextTkName;
        // "word 123"
        while(i < len && !isspace(sv.src[i]) && thisTkName == nextTkName){
            thisTkName = WT(sv.src[i]);
            nextTkName = WT(sv.src[i + 1]);
            result += sv.src[i];            


            ++i;
        }
        sv.count -= i;
        sv.src = sv.src.substr(i, len);
        return result;

    }
    std::string chopRight(SV::stringView &sv){
        uint64_t len = sv.src.length();
        uint64_t i = 0;
        std::string result;
        // "word 123"
        while(i < len && !isspace(sv.src[i])){
            result += sv.src[i];            
            ++i;
        }
        sv.count -= i;
        sv.src = sv.src.substr(i, len);
        return result;
    }
    std::string chopNext(SV::stringView &sv){
        SV::trimLeft(sv);
        return (SV::chopRight(sv));
    }
}
namespace Crossreference{
    void compilation_mode(std::vector<VR>& src){
        std::vector<uint64_t> blocks;
        uint64_t currentPosition{};
        for(auto& x : src){
	    if (    x.op == OP_IF
	        ||  x.op == OP_WHILE
	        ||  x.op == OP_DO){
	        blocks.push_back(currentPosition);
	    } else if (x.op == OP_END) {
	        if (blocks.size() < 1) continue;
	        auto last_block = blocks.back();
	        blocks.pop_back();
	                                                                            
	        if (src[last_block].op == OP_DO){
	            auto before_do = blocks.back();
	            blocks.pop_back();
	            if (src[before_do].op == OP_IF){
	        	src[last_block].operand = currentPosition;
	            }
	            else if (src[before_do].op == OP_WHILE){
	        	src[currentPosition].operand = before_do;
	        	src[last_block].operand = currentPosition;
	            }
	        }
	    }
	    ++currentPosition;
        }
	if (blocks.size() > 0){
	    fprintf(stderr, "ERROR: Unclosed do-end blocks. Use simulation mode for better error location\n");
	    exit(1);
	}

    }
    
    void simulation_mode(std::vector<Token> &src){
        std::vector<uint64_t> blocks;
        uint64_t currentPosition{};
//        for(std::vector<Token>::iterator x = src.begin(); x !=  src.end(); ++x){
        for(auto& x : src){
	    std::string ipname = x.head.atomName;
	    if (ipname == "if"
		|| ipname == "while"
		|| ipname == "do"){
		blocks.push_back(currentPosition);
	    } else if (ipname == "end") {
		if (blocks.size() < 1) continue;
		auto last_block = blocks.back();
		blocks.pop_back();

		if (src[last_block].head.atomName == "do"){
		    auto before_do = blocks.back();
		    blocks.pop_back();
		    if (src[before_do].head.atomName == "if"){
			src[last_block].head.atomLinkedIndex = currentPosition;
		    }
		    else if (src[before_do].head.atomName == "while"){
			src[currentPosition].head.atomLinkedIndex  = before_do + 1;
			src[last_block].head.atomLinkedIndex = currentPosition + 1;
		    }
		}
	    }
	    ++currentPosition;
        }
	if (blocks.size() > 0){
	    uint64_t unclosedBlock = blocks.back();
	    fprintf(stderr, "%lu:%lu: ERROR: Unclosed do-end blocks.\n",
		    src[unclosedBlock].head.atomIndexLine,
		    src[unclosedBlock].head.atomIndex
		    );
	    exit(1);
	}
    }
}
namespace Lexer{
    std::string Tokenize(std::string word, Token_Type &op){
        if(is_number(word)){
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
            op = STRING;
            return ("STRING_TYPE");
        }
    }
    void lex_line(std::vector<Token> &tokenVector, std::string source, uint64_t line){
        SV::stringView src = SV::SV(source);
        uint64_t  start = src.count;
        uint64_t  pos{};
        Token_Type           actualType;
        std::string          actualWorld;
        std::string          token;
        std::vector<Token>   tokenList;
        while(src.count > src.minimunValue){
            actualWorld = SV::separateByTokens(src);
	    if (actualWorld.length() ==  0 ) continue;
            pos = start - src.count;
            token = Lexer::Tokenize(actualWorld, actualType);
            tokenList.push_back(
                Token{
                    .type = actualType,
                    .head = Atom{
                        actualWorld, 
                        token, 
                        pos - actualWorld.length(),
                        line,
                        0
                    },
                }
            );
        }
        for(auto& token_after_lex : tokenList)
            tokenVector.push_back(token_after_lex);
    }
}


#endif /* ifndef LEXER */
