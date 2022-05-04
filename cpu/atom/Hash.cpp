#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <string>
#include <iterator>
#include <list>

class Hash
{
private:
    int maxItens;
    int maxPosition;
    int len;
    std::list<std::pair<int, std::string>> _hash;

private:
    int HashFunction(int __key){
        return (__key % this->maxPosition);
    }
public:
    Hash(int max_i,int max_p){
        this->maxItens      = max_i;
        this->maxPosition   = max_p;

        this->len   = 0;
        //this->_hash = new std::list<std::pair<int, std::string>>;
    }
    virtual ~Hash(){
        //delete this->_hash;
    }

    //bool isEmpty();
    bool isFull(){
        return (this->len == this->maxItens);
    }
    int getLen(){
        return (this->len);
    }
    void insert(int __key, std::string __item){
        {
            this->_hash.push_back(std::pair<int, std::string>(__key, __item));
        }
        this->len++;
    }
    void remove(int __key){
        {
            this->_hash.remove_if([__key, this](auto it){
                return it.first == __key;
                
            });
        }
        this->len--;
        
    }
    std::string searchFor(int __key){
        for (
                auto it = this->_hash.begin();
                it != this->_hash.end();
                ++it
            ){
                    if (it->first == __key){
                        return it->second;
                    }
                }
        return 0;
    }
    int searchForStr(std::string __key){
        for (
                auto it = this->_hash.begin();
                it != this->_hash.end();
                ++it
            ){
                if (it->second == __key){
                    return it->first;
                }
        }
        return -1;

    }
    void display(){
        for (
                auto it = this->_hash.begin();
                it != this->_hash.end();
                ++it
            ){
                std::cout << it->second << ", ";
        }

    }
};

#endif /* HASH_H */
