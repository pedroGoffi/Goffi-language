/*  TODO
 *      Document this better
 */

#ifndef LEXER_CPP
#define LEXER_CPP 




#include "./../includes/stdGoffi.cpp"
#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <vector>
#include <memory> 

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
                debug_lexer(tmp, this_tk, *idx);
                reset_str(tmp);
            }

            incPtr(idx);
        }
        debug_lexer(tmp, next_tk, *idx);
    }
}
#endif /* ifndef LEXER_CPP */
