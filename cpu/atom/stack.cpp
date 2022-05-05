#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
//#include <stdexcept>
//#include <unordered_map>
#include "./Hash.cpp"

template<typename T> class stack{
    private:
        T MAX;

    public:
        T len;
        T* Estrutura;
        std::string buffer_value;

        Hash *bss;

        stack(T MAX)
        {
            this->len = 0;
            this->MAX = MAX;
            this->Estrutura = new T [this->MAX];
            this->bss = new Hash(50, 50);
        }
        ~stack(){ 
            delete[]    this->Estrutura; 
            delete      this->bss;
        }
        bool isFull()  { return (this->len == this->MAX);}
        bool isEmpty() { return (this->len == 0); }
        void push(T item){
            if(this->isFull()){
                // TODO handle exception
                std::cout << "[ERROR] Stack is full\n";
                return;
            }
            this->Estrutura[this->len] = item;
            ++this->len;

        }
        T pop(){
            if(this->isEmpty()){
                return 0;
            }
            --this->len;
            return this->Estrutura[this->len];
        }
        T Len() { return this->len; }
        T last(){ return this->Estrutura[this->len-1]; }

        void storeAt(std::string name, T key){
          this->bss->insert(key, name);
          
        }
        T loadAt(std::string name){
            return (this->bss->searchForStr(name));
        }
        void buffer(std::string buff){
          this->buffer_value = buff;
        }
};

#endif /* ifndef STACK_HPP */
