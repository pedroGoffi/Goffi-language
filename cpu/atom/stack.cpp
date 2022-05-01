#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
template<typename T> class stack
{
    private:
        T len;
        T MAX;
        T* Estrutura;

    public:
        std::string aloc;
        stack(T MAX){
            this->len = 0;
            this->MAX = MAX;
            this->Estrutura = new T [this->MAX];
        }
        ~stack(){ delete[] this->Estrutura; }
        bool isFull()  { return (this->len == this->MAX); }
        bool isEmpty() { return (this->len == 0); }
        void display(){
            class stack<T> tmp = this->Estrutura;
            for( T i=0; i <= this->len; i++ ){
                std::cout << this->tmp[i] << " ";
            }
            delete tmp;
        }
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
        void str(std::string aloc){
          this->aloc = aloc;
        }
};

#endif /* ifndef STACK_HPP */
