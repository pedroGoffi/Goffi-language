#ifndef	STRING_VIEW 
#define	STRING_VIEW 
#include <cstdint>
#include<iostream>

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
    typedef struct stringView{
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
#endif /* ifndef STRING_VIEW */
