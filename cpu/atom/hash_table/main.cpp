#include <iostream>
#include <string>
#include "Hash.h"
int main(void)
{
    int size_vec = 13,  max = 6;
    std::cout
        << "The factor is: "
        << (float)max / (float)size_vec
        << "\n";

    Hash<int, std::string> myHash(size_vec, max);

    



    myHash.insert(1, "uwu1");
    myHash.insert(2, "uwu2");
    myHash.insert(3, "uwu3");
    myHash.insert(4, "uwu4");
    


    myHash.display();
    return 0;
}
