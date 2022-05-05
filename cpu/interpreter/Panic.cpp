#ifndef INCLUDE_PANIC_HANDLER
#define INCLUDE_PANIC_HANDLER 

#include <exception>
#include <string>
#include <cstdio>
/*
 *  PANIC
 *  @args <LINE ERROR> <CONTEXT ERROR>
 *  LINE ERROR YOU SAY WHEN YOUR CODE "PANICKED"
 *  WITH CONTEXT YOU DISPLAY IN THE SCREEN WHAT HAPPENED
 */
struct Panic : public std::exception{
protected:
    char buff[100];
public:
    const char* what() const noexcept{
        return this->buff;
    }
    explicit Panic(int line_err, const std::string _info) {
        sprintf(this->buff, "[PANIC-ERROR] | [LINE:%d] |\n\t[CONTEXT]: %s", line_err, _info.c_str());

    }
    virtual ~Panic() noexcept {}
};



#endif /* ifndef INCLUDE_PANIC_HANDLER */
