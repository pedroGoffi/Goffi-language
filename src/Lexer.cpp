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
    else if (w == '*')		return "MULT"

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
        std::vector<uint64_t> cR, eL;
        uint64_t currentPosition{};
//        for(std::vector<Token>::iterator x = src.begin(); x !=  src.end(); ++x){

        for(auto& x : src){
            if (x.op == OP_DO){
                cR.push_back(currentPosition);
                if(cR.size() > 0){
                    uint64_t if_ip = cR.back();
                    cR.pop_back();
                    src[if_ip].operand = currentPosition - if_ip;
                    cR.push_back(currentPosition);                                            
                }
            }
            else if (x.op == WHILE){
                cR.push_back(currentPosition);                
            }
            //else if (x.head.atomName == "elif"){
            //    uint64_t if_ip = cR.back();
            //    eL.push_back(currentPosition);
            //    if((src[if_ip].head.atomLinkedIndex) == 0){
            //        src[if_ip].head.atomLinkedIndex = currentPosition - if_ip + 1;
            //        src[currentPosition].head.atomLinkedIndex = currentPosition;
            //        cR.push_back(currentPosition);}
            //}
            else if (x.op == OP_ELSE){
                uint64_t if_ip = cR.back();
                cR.pop_back();
                src[if_ip].operand = currentPosition + 1;
                cR.push_back(currentPosition);
                if(eL.size() > 0){
                    uint64_t elif_ip = eL.back();
                    while(eL.size() > 0){
                        elif_ip = eL.back();
                        eL.pop_back();
                        src[elif_ip].operand = currentPosition - src[elif_ip].operand;
                    }
                }
            } 
            else if (x.op == OP_END){
                uint64_t if_ip = cR.back();
                cR.pop_back();
                src[if_ip].operand = currentPosition + 1;
                if(cR.size() > 0){
                    if_ip = cR.back();
                    cR.pop_back();

                    src[currentPosition].operand = if_ip;
                }
            }
            ++currentPosition;
        }
    }
    
    void simulation_mode(std::vector<Token> &src){
        std::vector<uint64_t> do_blocks;
        uint64_t currentPosition{};
//        for(std::vector<Token>::iterator x = src.begin(); x !=  src.end(); ++x){
        for(auto& x : src){
	    // simulation mode UwU
	    if (x.head.atomName == "do"){
		do_blocks.push_back(currentPosition);
	    }
	    else if (x.head.atomName == "end"){
		uint64_t do_ip = do_blocks.back();
		do_blocks.pop_back();
		src[do_ip].head.atomLinkedIndex = currentPosition;
	    }
            ++currentPosition;
        }
        size_t idx = 0;
        printf("    --- start ----\n");
        for(auto& x : src){
            std::cout 
                <<  "name:\t"      << x.head.atomName
                <<  "\tidx: "   << idx
                <<  "\tLidx: "  << x.head.atomLinkedIndex
                <<  std::endl;
            ++idx;
        }
        printf("    --- end ---\n");
        exit(1);
    }
}
namespace Lexer{
    std::string Tokenize(std::string word, Token_Type &op){
        if(is_number(word)){
            op = NUMBER;
            return ("NUMERICAL_TYPE");
        }	
        else if (word == "+"){
            op = BINARY_OPERAND;
            return ("OP_PLUS");
        }
        else if (word == "-"){
            op = BINARY_OPERAND;
            return ("OP_MINUS");
        }
	else if (word == "*"){
	    op = BINARY_OPERAND;
	    return ("OP_MULT");
	}
        
        else if (word == "<"){
            op = BINARY_OPERAND;
            return ("OP_CMP_LT");
        }
        else if (word == ">"){
            op = BINARY_OPERAND;
            return ("OP_CMP_GT");
        }
        else{
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
            if(actualWorld.length() ==  0 ) continue;

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
