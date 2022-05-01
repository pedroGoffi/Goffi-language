#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <iostream>

class Queue
{
private:
    int first, last, MAX;
    int* Estrutura;

public:
    Queue(int MAX);
    virtual ~Queue();
    bool isEmpty();
    bool isFull();
    void enqueue(int item); // similar to push
    int dequeue(); // similar to pop
    void display();

};
Queue::Queue(int MAX){
    this->first = 0;
    this->last  = 0;
    this->MAX   = MAX;
    this->Estrutura = new int[this->MAX];

}
Queue::~Queue(){
    delete[] this->Estrutura;
}
bool Queue::isEmpty(){
    return (first == last);
}
bool Queue::isFull(){
    return (this->last - this->first == this->MAX);
}
void Queue::enqueue(int item){
    if(this->isFull()){
        std::cout << "[ERROR] this queue is full\n";
        return;
    }
    this->Estrutura[this->last % this->MAX] = item;
    this->last++;

}
int Queue::dequeue(){
    if(this->isEmpty()){
        std::cout << "[ERROR] Cant remove item from this queue";
        return 0;
    }
    this->first++;
    return this->Estrutura[(this->first-1) % this->MAX];

}
void Queue::display(){
    std::cout << "[";
    for ( size_t i=this->first; this->last; ++i ){
        std::cout << this->Estrutura[ i % this->MAX ] << ", ";
    }
    std::cout << "]\n";
}
#endif /* ifndef QUEUE_CPP */ 
