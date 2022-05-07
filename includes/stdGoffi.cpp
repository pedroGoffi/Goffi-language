/*  TODO
 *      Document this better
 */


#ifndef GENERAL_FUNCTIONS_USE
#define GENERAL_FUNCTIONS_USE 

#define debug                               true

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
    if(debug) std::cout<<"[INDEX]:("<<idx<<")[LEXER][WORD-PARSED] :\t"<<x<<"\t[TYPE] :\t"<<type<<"\n"

#define debug_parser(x, type, idx)          \
    if(debug) std::cout<<"[INDEX]:("<<idx<<")[PARSER][WORD-PARSER] :\t"<<x<<"\t[TYPE] :\t"<<type<<"\n"



#endif /* ifndef GENERAL_FUNCTIONS_USE */
