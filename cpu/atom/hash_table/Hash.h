#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <list>

template<typename _type, typename _value> class Hash
{
private:
    int maxItens;
    int maxPosition;
    int len;
    std::list<std::pair<_type, _value>>* _hash;

private:
    int HashFunction(_type __key){
        return (__key % this->maxPosition);
    }
public:
    Hash<_type, _value>(int max_i,int max_p){
        this->maxItens      = max_i;
        this->maxPosition   = max_p;

        this->len   = 0;
        this->_hash = new std::list<std::pair<_type, _value>>;
    }
    virtual ~Hash<_type, _value>(){
        delete this->_hash;
    }

    //bool isEmpty();
    bool isFull(){
        return (this->len == this->maxItens);
    }
    int getLen(){
        return (this->len);
    }
    void insert(_type __key, _value __item){
        {
            int _loc_var = this->HashFunction(__key);
            // TODO:
            //  insert procedure
            std::cout << "uwu " << __item << "\n";
            //this->_hash[_loc_var] = __item;
        }
        this->len++;
    }
    void remove(_type __key){
        {
            int _loc_var = this->HashFunction(__key);
            this->_hash[_loc_var] = -1;
        }
        this->len--;

    }
    void searchFor(_type __key){
        std::cout << "TODO\n";
        // TODO
    }
    void display(){
        // TODO
        std::cout << "ok\n";
    }
};

#endif /* HASH_H */
