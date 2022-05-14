#ifndef LEXING_STAGE_H
#define LEXING_STAGE_E 
#include <cassert>
#include <string>
#include <cstdio>
void usage(const char* program);
char *shift(int *argc, char ***argv);
bool is_number(const std::string& str);
#ifdef T_IMPLS
    #include "./Tools.hpp"
#endif
#endif /* ifndef LEXING_STAGE_H */
