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

#define debug                               true

#define sPtrType                            unsigned
#define ptrType                             std::shared_ptr<sPtrType>
#define sPtr                                std::make_shared<sPtrType>

#define tokenAtom                           char
#define tokenType                           std::string
#define tokenName                           std::string
#define tokenList                           std::vector<tokenPair>
#define tokenPair                           std::pair<tokenName, tokenType>

#define tokensPair(value, type)             std::pair<tokenName, tokenType>(value, type)
#define skipblank(vec, idx)                 if (vec[*idx].second == "__BLANK__") incPtr(idx)
#define space(x)                            std::isspace(x)
#define digit(x)                            std::isdigit(x)
#define letter(x)                           std::isalpha(x)

#define chrcmp(x, y)                        (x == y)
#define strcmp(x, y)                        (std::string(&x) == y)

#define loadPtr(var, initValue)             ptrType var = (sPtr)(initValue)

#define incPtr(ptr)                         ptr = sPtr(*ptr+1)
#define resetPtr(ptr)                       ptr = sPtr(0)
#define thisTk(src, idx)                    token_type(src[idx])
#define reset(str)                          str = ""
#define initTmp(name)                       std::string name = "";

#define debug_lexer(x, type)                if (debug) std::cout << "[LEXER][WORD-PARSED] :\t" << x << "\t[TYPE] :\t"<< type << "\n"

typedef enum {
    INT
} tkType;

typedef enum {
    OP_PLUS,         // +
    OP_DIV,          // /
    OP_SUB,          // -
    OP_MULT,         // *
    OP_ASIGN_VAR     // =    
} opType;

namespace Lexer{
    tokenType token_type(tokenAtom atom){
        if     (space(atom))            return "__BLANK__";
        else if(digit(atom))            return "INT";
        else if(letter(atom))           return "STR";
    
        else if(chrcmp(atom, '+'))      return "OP_PLUS";
        else if(chrcmp(atom, '-'))      return "OP_SUB";
        else if(chrcmp(atom, '/'))      return "OP_DIV";
        else if(chrcmp(atom, '*'))      return "OP_MULT";
    
        else if(chrcmp(atom, '='))      return "OP_ASIGN_VAR";
    
        else if(chrcmp(atom, '('))       return "OPEN_CIRCULAR_BRACKETS";
        else if(chrcmp(atom, ')'))       return "CLOSE_CIRCULAR_BRACKETS";
    
        else if(chrcmp(atom, '['))       return "CLOSE_SQUARE_BRACKETS";
        else if(chrcmp(atom, ']'))       return "CLOSE_SQUARE_BRACKETS";
    
        else if(chrcmp(atom, '{'))       return "OPEN_CURLY_BRACKETS";
        else if(chrcmp(atom, '}'))       return "CLOSE_CURLY_BRACKETS";
    
        else if(chrcmp(atom, ';'))       return "OP_EOL";
    
    
        else if(chrcmp(atom, '"'))       return "STR_INIT_DQ";
        else if(strcmp(atom, "'"))       return "STR_INIT_SQ";
    
    
        else if(chrcmp(atom, ','))       return "COMMA";
        else if(chrcmp(atom, '_'))       return "STR";


        else if(chrcmp(atom, EOF))       return "__EOF__";
        else if(chrcmp(atom, '\0'))      return "__EOF__";

        return "UNKNOWN-TOKEN";
    }
    void run(tokenName src, ptrType& idx, tokenList& tkVec){
        tokenType this_tk;
        tokenType next_tk;    
        initTmp(tmp);
        src[src.length() + 1] = EOF; 
        
        for (;src[*idx] != EOF;){
            this_tk = thisTk(src, *idx);
            next_tk = thisTk(src, *idx + 1);
            tmp += src[*idx];
            if (this_tk != next_tk){
                if (this_tk != "__BLANK__")
                    tkVec.push_back(tokensPair(tmp, this_tk));
                debug_lexer(tmp, this_tk);
                reset(tmp);
            }

            incPtr(idx);
        }
        debug_lexer(tmp, next_tk);
    }
}
#endif /* ifndef LEXER_CPP */
