#ifndef JSTACK_H
#define JSTACK_H

#include <iostream>

using namespace std;

class Jstack
{
private:
    int *stack;
    int count;
    int lenStack;
    void expandArray(); // aumenta o tamanho do array
    void reduceArray(); // diminui o tamanho do array
public:
    Jstack();
    ~Jstack();

    void push(int); //inclui um elemento no topo da pilha
    int top();  // retorna o valor no topo da pilha
    void pop(); // remove um elemento

};

#endif //JSTACK_H