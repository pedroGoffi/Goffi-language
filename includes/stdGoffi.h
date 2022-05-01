#ifndef MAIN_PROGRAM_INCLUDES
#define MAIN_PROGRAM_INCLUDES

#include <iostream>
#include <string>    

#ifndef OPEN_FILE
    #include <fstream>
#endif
namespace gff{
    void onError(std::string cause){
        std::cout <<"[ERROR] "<<cause<<"\n";
        exit(1);
    }
};
#endif /* ifndef MAIN_PROGRAM_INCLUDES */
