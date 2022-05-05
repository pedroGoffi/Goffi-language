#ifndef HASH_H
#define HASH_H
#include <iostream>
// TODO: impl my own hash func

#include "./Hashing/GeneralHashFunctions.cpp"
#include "./Hashing/GeneralHashFunctions.h"
#include <string>
#include <vector>
#define max_hash_value 1024

class Hash{
private:
    int maxItens;
    int maxPosition;
    int len;
    std::vector<std::pair<int, std::string>> _hash = std::vector<std::pair<int, std::string>>(max_hash_value);

private:
    int HashFunction(std::string __key){
        return ELFHash(__key);
    }
public:
    Hash(int max_i,int max_p){
        this->len   = 0;
        this->maxItens      = max_i;
        this->maxPosition   = max_p;
    }

    bool isEmpty(){
        return (this->len == 0);
    }
    bool isFull(){
        return (this->len == this->maxItens);
    }
    int getLen(){
        return (this->len);
    }
    void insert(int __key, std::string __item){
        {
            this->_hash[this->HashFunction(__item)] = (std::pair<int, std::string>(__key, __item));
        }
        this->len++;
    }
    void remove(std::string __key){
        {
            this->_hash.erase(this->_hash.begin() + this->HashFunction(__key));
        }        
        this->len--;
        
    }
    int searchForStr(std::string __key){
        for(auto& v : this->_hash){
            if (v.second == __key) {
                return (v.first);
            }
        }
        return -1;
    }
    void display(){
        for (auto it = this->_hash.begin();it != this->_hash.end();++it){
            std::cout 
                << "("  << it->first
                << ", " << it->second
                << ")";
        }

    }
};

#endif /* HASH_H */
