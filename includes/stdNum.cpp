#ifndef NUMBER_OPERATIONS
#define NUMBER_OPERATIONS 

#include <string>

namespace gff{
  int parseHex(std::string hex_num){
    return std::stoi(hex_num, 0, 16);
  }
  bool is_number(const std::string& str){
      for(char const &c : str){
          if (std::isdigit(c) == 0) return false;
      }
      return true;
  }
}
#endif /* ifndef NUMBER_OPERATIONS */
