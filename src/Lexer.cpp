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
#define space(x)                            std::isspace(x)
#define digit(x)                            std::isdigit(x)
#define letter(x)                           std::isalpha(x)

#define chrcmp(x, y)                        (x == y)
#define strcmp(x, y)                        (std::string(&x) == y)

#define loadPtr(var, initValue)             ptrType var = (sPtr)(initValue)
#define incPtr(ptr)                         ptr = sPtr(*ptr+1)
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

    return "UNKNOWN-TOKEN";
}
tokenName lexer_this(tokenName src, ptrType& idx, tokenList& tkVec){
    tokenType this_tk;
    tokenType next_tk;

    initTmp(tmp);
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
            if (space(src[*idx]) || (this_tk != next_tk)){
                tkVec.push_back(tokensPair(tmp, this_tk));

                debug_lexer(tmp, this_tk);
                reset(tmp);
            }
            tmp += src[*idx];
            incPtr(idx);                
        }
        tkVec.push_back(tokensPair(tmp, next_tk));
        debug_lexer(tmp, next_tk);
    } else{
        this_tk = thisTk(src, *idx);
        tkVec.push_back(tokensPair(std::string(&src[0]), this_tk));
        debug_lexer(src[0], this_tk);
    }
    
    return "69";
}
tokenList tokenize_this(tokenName src_code){
    tokenList tokenVec;
    loadPtr(index, 0);
    lexer_this(src_code, index, tokenVec);
    for(auto& vec : tokenVec){
        if (std::string(vec.second) == "__BLANK__") continue;
        std::cout << "[VEC] =\t" << vec.first << "\t| " << vec.second << "\n";
        
    }
    
    exit(0);
}
int main(void){
    /* TODO:
     *      How it will bre implemented by vim_dot
     *      fix initial index bug in the tokenizer
     */
    tokenName src_code =
        "proc main(int argc, char** argv){"
            "write(\"Hello world!\");" 
            "char value[69];" 
            "stdin(value, \"What is your name\";"
            "stdout(\"You said ${s}\",value);"
        "}";

    tokenList Tokenized = tokenize_this(src_code);
    return 0;    
}
#endif /* ifndef LEXER_CPP */
