#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
//#include <stdexcept>
#include <unordered_map>

template<typename T> class stack
{
    private:
        T MAX;

    public:
        T len;
        std::unordered_map<T, std::string> bss;
        T* Estrutura;
        std::string buffer_value;
        stack(T MAX){
            this->len = 0;
            this->MAX = MAX;
            this->Estrutura = new T [this->MAX];
        }
        ~stack(){ delete[] this->Estrutura; }
        bool isFull()  { return (this->len == this->MAX);}
        bool isEmpty() { return (this->len == 0); }
        void push(T item){
            if(this->isFull()){
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

        void storeAt(std::string name, T value){
          // FIXME
          //    this->bss.insert(std::pair<T, std::string>(value, name));
          
        }
        T loadAt(std::string name){
            // FIXME            
            //  return this->bss[name];
        }
        void buffer(std::string buff){
          this->buffer_value = buff;
        }
};

#endif /* ifndef STACK_HPP */
