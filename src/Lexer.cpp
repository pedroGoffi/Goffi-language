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
    size_t      atomIndex;
    size_t      atomLinkedIndex;
};
typedef enum{
    NUMBER,
    BINARY_OPERAND,
    STRING_LITERAL
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

    return "__BlANK__";
}
namespace SV{
    size_t countChar(std::string src){
        size_t i = 0;
        size_t len = src.length();
        while(i <= len){
            i += 1;
        }
        return i;
    }
    typedef struct {
        size_t      count;
        std::string src;
        size_t      minimunValue = 1;
    }stringView;

    stringView SV(std::string src, size_t count = 0){
        stringView sv;
        sv.count = (count == 0) 
            ? SV::countChar(src)
            : count;
        sv.src   = src;
        return sv;
    }
    
    void trimLeft(SV::stringView &sv){

        size_t len = sv.src.length();
        size_t index = 0;

        while(index < len && isspace(sv.src[index])){
            ++index;
        }
        sv.count -= index;
        sv.src = sv.src.substr(index, sv.src.length());
    }
    std::string separateByTokens(SV::stringView &sv){
        SV::trimLeft(sv);
        size_t len = sv.src.length();
        size_t i = 0;
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
        size_t len = sv.src.length();
        size_t i = 0;
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
namespace Lexer{
    std::vector<Token> crossReference(std::vector<Token> &src){
        std::vector<size_t> cR, eL;
        size_t currentPosition{};
        for(std::vector<Token>::iterator x = src.begin(); x !=  src.end(); ++x){

            if (x->head.atomName == "do"){
                cR.push_back(currentPosition);
                if(cR.size() > 0){
                size_t if_ip = cR.back();
                    cR.pop_back();
                    src[if_ip].head.atomLinkedIndex = currentPosition - if_ip;
                    cR.push_back(currentPosition);                                            
                }
            }
            else if (x->head.atomName == "while"){
                cR.push_back(currentPosition);                
            }
            else if (x->head.atomName == "elif"){
                size_t if_ip = cR.back();
                eL.push_back(currentPosition);
                if((src[if_ip].head.atomLinkedIndex) == 0){
                    src[if_ip].head.atomLinkedIndex = currentPosition - if_ip + 1;
                    src[currentPosition].head.atomLinkedIndex = currentPosition;
                    cR.push_back(currentPosition);}
            }
            else if (x->head.atomName == "else"){
                size_t if_ip = cR.back();
                cR.pop_back();
                src[if_ip].head.atomLinkedIndex = currentPosition - if_ip + 1;
                cR.push_back(currentPosition);
                if(eL.size() > 0){
                    while(eL.size() > 0){
                        size_t elif_ip = eL.back();
                        eL.pop_back();
                        src[elif_ip].head.atomLinkedIndex = currentPosition - src[elif_ip].head.atomLinkedIndex;
                    }
                }
                
            } 
            else if (x->head.atomName == "end"){
                size_t if_ip = cR.back();
                cR.pop_back();
                src[if_ip].head.atomLinkedIndex = currentPosition - if_ip + 1;
                if(cR.size() > 0){
                    if_ip = cR.back();
                    cR.pop_back();
                    src[currentPosition].head.atomLinkedIndex = currentPosition - if_ip;
                }
            }
            ++currentPosition;
        }
        return src;
    }
    std::string Tokenize(std::string word, Token_Type &op){
        if(is_number(word)){
            op = NUMBER;
            return ("INT");
        }
        else if (word == "+"){
            op = BINARY_OPERAND;
            return ("OP_PLUS");
        }
        else if (word == "-"){
            op = BINARY_OPERAND;
            return ("OP_MINUS");
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
            op = STRING_LITERAL;
            return ("STR");
        }
    }
    std::vector<Token> lex(std::string source){
        SV::stringView src = SV::SV(source);
        size_t  start = src.count;
        size_t  pos{};
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
                        pos,
                        0
                    },
                }
            );
        }
        Lexer::crossReference(tokenList);
        return tokenList;
    }
}


#endif /* ifndef LEXER */
