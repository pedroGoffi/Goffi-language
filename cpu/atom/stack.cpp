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
        stack(T MAX){
            this->len = 0;
            this->MAX = MAX;
            this->Estrutura = new T [this->MAX];
        }
        ~stack(){ delete[] this->Estrutura; }
        bool isFull()  { return (this->len == this->MAX); }
        bool isEmpty() { return (this->len == 0); }
        void display(){
            std::cout<<"STACK: [ ";
            for( T i=0; this->len; i++ ){
                std::cout << this->Estrutura[i] << ", ";
            }
            std::cout << "]\n";                                 
        }
        void push(T item){
            if(this->isFull()){
                std::cout << "[ERROR] Stack is full\n";
                return;
            }
            this->Estrutura[this->len+1] = item;
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
        T last(){ return this->Estrutura[this->MAX]; }
};

#endif /* ifndef STACK_HPP */
