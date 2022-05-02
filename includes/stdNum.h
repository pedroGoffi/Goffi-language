#ifndef NUMBER_OPERATIONS
#define NUMBER_OPERATIONS 
#include "./stdGoffi.h"
namespace gff{
  int parseHex(std::string hex_num){
    return std::stoi(hex_num, 0, 16);
  }
}
#endif /* ifndef NUMBER_OPERATIONS */
