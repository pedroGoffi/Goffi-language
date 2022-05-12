/*  TODO
 *      Document this better
 */

#ifndef LEXER_CPP
#define LEXER_CPP 

#define DOUBLE_QUOTES 0x22
#define SINGLE_QUOTES 0x27


#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
#include "./../includes/stdGoffi.cpp"
#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <memory> 

#define debug_cross(x) std::cout << "[CROSSREfERENCE][WORD] :\t" << x.first << "\t[TYPE] :\t" << x.second << "\n"

namespace Lexer{
    tokenList crossReference(tokenList& vec){
        int    lastNode{};
        int    atualNode{};
        for(auto it = vec.begin(); it != vec.end(); ++it){
            if(vec[atualNode].first == "if"){
                lastNode = atualNode;
            }
            else if (vec[atualNode].first == "elif"){
                vec[lastNode] = std::pair<tokenName, tokenType>(vec[lastNode].first, std::to_string(atualNode));
                atualNode = lastNode;

                std::cout << "[CHANGED] :\t" << vec[lastNode].first << "\t[REF] :\t" << vec[lastNode].second;
                
            }
            else if (vec[atualNode].first == "else"){
                vec[lastNode] = std::pair<tokenName, tokenType>(vec[lastNode].first, std::to_string(atualNode + 1));
                atualNode = lastNode;

                std::cout << "[CHANGED] :\t" << vec[lastNode].first << "\t[REF] :\t" << vec[lastNode].second;
            }
            debug_cross(vec[atualNode]);
            ++atualNode;
        }
        for(auto& c : vec){
            std::cout <<    "AFTER-CROSSREFERENCE : "
                      <<    c.first 
                      <<    "\t[REF] :\t" 
                      <<    c.second
                      <<    "\n";

        }
        return vec;
    }
    tokenType token_type(tokenAtom atom){
        if     (space(atom))            return "__BLANK__";
        else if(digit(atom))            return "INT";
        else if(letter(atom))           return "STR";
    
        else if(chrcmp(atom, '+'))      return "OP_PLUS";
        else if(chrcmp(atom, '-'))      return "OP_SUB";
        else if(chrcmp(atom, '/'))      return "OP_DIV";
        else if(chrcmp(atom, '*'))      return "OP_MULT";
    
        else if(chrcmp(atom, '='))      return "OP_ASIGN_VAR";
    
        else if(chrcmp(atom, '('))      return "OPEN_CIRCULAR_BRACKETS";
        else if(chrcmp(atom, ')'))      return "CLOSE_CIRCULAR_BRACKETS";
    
        else if(chrcmp(atom, '['))      return "CLOSE_SQUARE_BRACKETS";
        else if(chrcmp(atom, ']'))      return "CLOSE_SQUARE_BRACKETS";
    
        else if(chrcmp(atom, '{'))      return "OPEN_CURLY_BRACKETS";
        else if(chrcmp(atom, '}'))      return "CLOSE_CURLY_BRACKETS";
    
        else if(chrcmp(atom, ';'))      return "OP_EOL";
    
    
        else if(chrcmp(atom, '\"'))     return "STR_INIT_DQ";
        else if(chrcmp(atom, '\''))     return "STR_INIT_SQ";
    
    
        else if(chrcmp(atom, ','))      return "COMMA";
        else if(chrcmp(atom, '_'))      return "STR";  
        else if(chrcmp(atom, '>'))      return "CMP_GT";
        else if(chrcmp(atom, '<'))      return "CMP_LT";

        else if(chrcmp(atom, '.'))      return "DOT";

        else if(chrcmp(atom, EOF))      return "__EOF__";
        else if(chrcmp(atom, '\0'))     return "__EOF__";

        char err_log[128];
        sprintf(err_log, "Unreachable token at the word: (%c)", atom);
        gassert(false, err_log);
    }
    void lex_string_literal(tokenName src, ptrType& idx, tokenList& tkvec, tokenAtom expect_tk){
        { /*  ADDING THE INITIAL QUOTES */

            const tokenName tmpSrc = std::string(&expect_tk);
            tokenType tmpTk  = thisTk(src, *idx);
            tkvec.push_back(tokensPair(std::string((&tmpSrc)[0]), tmpTk));
            debug_lexer(tmpSrc[0], tmpTk, *idx);

            incPtr(idx);
        }
        /*   STRING LEXING ITSELF */

        tokenName str;
        for(;src[*idx] != expect_tk;){
            str += src[*idx];
            incPtr(idx);
        }
        tkvec.push_back(tokensPair(str, "STRING_LITERAL"));
        debug_lexer(str, "STRING LITERAL", *idx);
        /*  END OF LEXING STRING */
        {
            const tokenName tmpSrc = std::string(&expect_tk);
            tokenType tmpTk  = thisTk(src, *idx);
            tkvec.push_back(tokensPair(std::string((&tmpSrc)[0]), tmpTk));
            debug_lexer(tmpSrc[0], tmpTk, *idx);        
            incPtr(idx);

        }
    }
    tokenList run(tokenName src, ptrType& idx){
        tokenType this_tk = thisTk(src, *idx);
        tokenType next_tk = thisTk(src, *idx + 1);    
        tokenList tkVec;
        initTmp(tmp);
        src[src.length() + 1] = EOF;         
        for (;src[*idx] != EOF;){
           
            lexer_literal_macro("STR_INIT_DQ", DOUBLE_QUOTES);
            lexer_literal_macro("STR_INIT_SQ", SINGLE_QUOTES);

            this_tk = thisTk(src, *idx);
            if(this_tk == "STR_INIT_DQ" || this_tk == "STR_INIT_SQ")
                continue;
            tmp += src[*idx];
            next_tk = thisTk(src, *idx + 1);
            
            if (this_tk != next_tk){
                if (this_tk != "__BLANK__")
                    tkVec.push_back(tokensPair(tmp, this_tk));
                debug_lexer(tmp, this_tk, *idx);
                reset_str(tmp);
            }


            if (next_tk == "__EOF__"){
                break;
            }
            incPtr(idx);
        }
        debug_lexer(tmp, next_tk, *idx);        
        return crossReference(tkVec);
    }

}
#endif /* ifndef LEXER_CPP */
