#ifndef LEXING_STAGE_SRC_CODE
#define LEXING_STAGE_SRC_CODE value
#include "./Tools.h"

void usage(FILE *stream, std::string program){
    /*  Since prinf has a beatiful sintax i'll use it instead of std::cout  */
    fprintf(stream, "Usage: %s [OPTIONS] <input.goffi>\n", program.c_str());
    fprintf(stream, "OPTIONS:\n");
    fprintf(stream, "    -h          print this help in stdout\n");
    fprintf(stream, "    -o <path>   provide output path\n");
}
char *shift(int *argc, char ***argv){
    assert(*argc > 0);
    char* result = **argv;
    *argv += 1;
    *argc -= 1;
    return result;
}
bool is_number(const std::string& str){
    for(char const &c : str){
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

#endif /* ifndef LEXING_STAGE_SRC_CODE */
