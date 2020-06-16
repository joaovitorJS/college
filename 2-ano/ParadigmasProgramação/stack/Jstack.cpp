#include "Jstack.h"


Jstack::Jstack()
{
    this->stack = new int[4];
    this->count = 0;
    this->lenStack = 4;
}

void Jstack::expandArray() {
    int *stackAux;
    int i;

    stackAux = new int[this->lenStack];
    for (i = 0; i < this->lenStack; i++) {
        stackAux[i] = this->stack[i];
    }

    delete stack;

    this->stack = new int[this->lenStack+4];

    for (i = 0; i < this->lenStack; i++) {
        this->stack[i] = stackAux[i];
    }

    delete stackAux;

    this->lenStack += 4;
}

void Jstack::reduceArray() {
    int *stackAux;
    int i;

    this->lenStack -= 4;

    stackAux = new int[this->lenStack];
    for (i = 0; i < this->lenStack; i++) {
        stackAux[i] = this->stack[i];
    }

    delete stack;

    this->stack = new int[this->lenStack];

    for (i = 0; i < this->lenStack; i++) {
        this->stack[i] = stackAux[i];
    }

    delete stackAux;
}

void Jstack::push(int value) {

    if (this->count < this->lenStack) {
        this->stack[this->count] = value;
        this->count++;
    } else {
        expandArray();
        this->stack[this->count] = value;
        this->count++;
    }
}

int Jstack::top() {
    return this->stack[count-1];
}

void Jstack::pop() {
    if(this->count > 0) {
        this->count--;
        if ((this->count * 2) == this->lenStack && (this->count % 4 == 0) && (this->lenStack > 4) ) {
            reduceArray();
        }
    } else {
        cout << "Pilha Vazia!" << endl;
    }
}

Jstack::~Jstack()
{
    delete this->stack;
}
