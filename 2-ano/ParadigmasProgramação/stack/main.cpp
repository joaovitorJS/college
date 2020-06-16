#include <iostream>
#include "Jstack.h"

using namespace std;

int main() {
    Jstack stack;

    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    cout <<"Topo: " << stack.top() << endl;

    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();

    stack.push(2);    
    
    cout <<"Topo: " << stack.top() << endl;

    return 0;
}