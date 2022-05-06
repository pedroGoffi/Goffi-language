/*  TODO
 *      Document this better
 */

#ifndef LEXER_CPP
#define LEXER_CPP 
#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <vector>
#include <memory> 


#define sPtrType                            unsigned
#define ptrType                             std::shared_ptr<sPtrType>
#define sPtr                                std::make_shared<sPtrType>

#define tokenAtom                           char
#define tokenType                           std::string
#define tokenName                           std::string
#define tokenList                           std::vector<tokenPair>
#define tokenPair                           std::pair<tokenName, tokenType>

#define tokensPair(value, type)             std::pair<tokenName, tokenType>(value, type)
#define space(x)                            std::isspace(x)
#define digit(x)                            std::isdigit(x)
#define letter(x)                           std::isalpha(x)
#define chrcmp(x, y)                        (x == y)
#define loadPtr(var)                        ptrType var = sPtr
#define incPtr(ptr)                         ptr = sPtr(*ptr+1)
#define thisTk(src, idx)                    token_type(src[idx])
#define reset(str)                       str = ""

#define debug(x, type)                            std::cout << "[WORD-PARSED] :\t" << x << "\t[TYPE] : "<< type << "\n"
typedef enum {
    INT
} tkType;

typedef enum {
    PLUS, // +
    DIV,  // /
    SUB,  // -
    MULT  // *
} opType;

tokenType token_type(tokenAtom atom){
    if     (space(atom))            return "__BLANK__";
    else if(digit(atom))            return "INT";
    else if(letter(atom))           return "STR";
    else if(chrcmp(atom, '+'))      return "PLUS";
    else if(chrcmp(atom, '-'))      return "SUB";
    else if(chrcmp(atom, '/'))      return "DIV";
    else if(chrcmp(atom, '*'))      return "MULT";

    else if(chrcmp(atom, '='))      return "OP_ASIGN_VAR";

    else if(chrcmp(atom, '('))       return "OPEN_CIRCULAR_PARAM";
    else if(chrcmp(atom, ')'))       return "CLOSE_CIRCULAR_PARAM";
    return "NOT-IMPLEMENTED-YET";
}
tokenName lexer_this(tokenName src, ptrType& idx, tokenList& tkVec){
    tokenType this_tk;
    tokenType next_tk;
    std::string tmp = "";
    if(src.length() > 1){
        /*  TODO
         *      better lexing stage
         *      for functions()
         */
        for (;*idx < src.length();){
            if (*idx > 0){
                this_tk     =   thisTk(src, *idx - 1);
                next_tk     =   thisTk(src, *idx);
            } else {
                this_tk     =   thisTk(src, *idx);
                next_tk     =   thisTk(src, *idx + 1);
            }
            if (space(src[*idx]) && (this_tk != next_tk)){
                tkVec.push_back(tokensPair(tmp, this_tk));
                debug(tmp, this_tk);
                reset(tmp);
            }
            tmp += src[*idx];
            incPtr(idx);                
        }
        tkVec.push_back(tokensPair(tmp, next_tk));
        debug(tmp, next_tk);
    } else{
        this_tk = thisTk(src, *idx);
        tkVec.push_back(tokensPair(std::string(&src[0]), this_tk));
        debug(src[0], this_tk);
    }
    
    return "69";
}
tokenList tokenize_this(tokenName src_code){
    tokenList tokenVec;
    loadPtr(index)(0);
    lexer_this(src_code, index, tokenVec);
    for(auto& vec : tokenVec){        
        std::cout << "[VEC] =\t" << vec.first << "\t| " << vec.second << "\n";
    }
    
    exit(0);
}
int main(void){
    /* TODO:
     *      How it will bre implemented by vim_dot
     */
    tokenName src_code ="1 + 1";
    tokenList Tokenized = tokenize_this(src_code);
    return 0;    
}
#endif /* ifndef LEXER_CPP */
