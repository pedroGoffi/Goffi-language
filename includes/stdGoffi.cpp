/*  TODO
 *      Document this better
 */

#ifndef GENERAL_FUNCTIONS_USE
#define GENERAL_FUNCTIONS_USE 

#include <cstdlib>
#include <cstdio>

#define debug                               false

#define sPtrType                            unsigned
#define ptrType                             std::shared_ptr<sPtrType>
#define sPtr                                std::make_shared<sPtrType>
#define loadPtr(var, initValue)             ptrType var = (sPtr)(initValue)
#define incPtr(ptr)                         ptr = sPtr(*ptr+1)
#define resetPtr(ptr)                       ptr = sPtr(0)

#define token_usage
#define tokenAtom                           char
#define tokenType                           std::string
#define tokenName                           std::string
#define tokenList                           std::vector<tokenPair>
#define tokenPair                           std::pair<tokenName, tokenType>
#define tokensPair(value, type)             std::pair<tokenName, tokenType>(value, type)
#define thisTk(src, idx)                    token_type(src[idx])

#define skipblank(vec, idx)                 if (vec[*idx].second == "__BLANK__") incPtr(idx)
#define space(x)                            std::isspace(x)
#define digit(x)                            std::isdigit(x)
#define letter(x)                           std::isalpha(x)
#define chrcmp(x, y)                        (x == y)
#define strcmp(x, y)                        (std::string(&x) == y)

#define reset_str(str)                          str = ""
#define initTmp(name)                       std::string name = "";

#define debug_lexer(x, type, idx)           \
    if(debug) std::cout<<"[INDEX : "<<idx<<"][LEXER][WORD-PARSED] :\t"<<x<<"\t[TYPE] :\t"<<type<<"\n"

#define lexer_literal_macro(strTk, expect)         if (this_tk == strTk)Lexer::lex_string_literal(src, idx, tkVec, expect)


#define debug_parser(x, type)          \
    if(debug) std::cout<<"[PARSER][WORD-PARSER] :\t"<<x<<"\t[TYPE] :\t"<<type<<"\n"


#define gassert(x, message) if (!(x)) {printf("\x1b[38m[File: %s] [Line: %d] [Functions: %s] [Assert: %s] \n\t[Message]:\x1B[31m %s\n\x1B[0m",__FILE__, __LINE__,__func__, #x, message); exit(1);}

#endif /* ifndef GENERAL_FUNCTIONS_USE */
