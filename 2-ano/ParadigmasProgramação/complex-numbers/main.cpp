#include <iostream>
#include "ComplexNumbers.h"

using namespace std;

int main() {
    // obs: ComplexNumbers(real, imaginaria)
    ComplexNumbers z1(3, 2), z2(5, -3), z3;

    z3 = z1 + z2;  //8, -1

    cout << "Adicao:\n";
    z3.printNumber(); 

    z1.setNumber(7, 10);
    z2.setNumber(3, 6);

    z3 = z1 - z2; //4, 4

    cout << "\nSubtracao:\n";
    z3.printNumber(); 

    z1.setNumber(2, 5);
    z2.setNumber(1, 3);

    z3 = z1 * z2; //-13, 11

    cout << "\nMultiplicacao:\n";
    z3.printNumber(); 

    z1.setNumber(20, -4);
    z2.setNumber(3, 2);

    z3 = z1 / z2; //4, -4

    cout << "\nDivisao:\n";
    z3.printNumber(); 

    z3 = z1; //20, -4

    cout << "\nAtribuicao:\n";
    z3.printNumber(); 


    cout << "\n""Igual a"": " << (z3 == z1) << endl;   // true
    cout << """Igual a"": " << (z3 == z2) << endl;   // false

    cout << "\n""Diferente de"": " << (z3 == z1) << endl;  // false
    cout << """Diferente de"": " << (z3 == z2) << endl;  // true

    ++z3; // 21, -3

    cout << "\n++Pre-Fixado:\n";
    z3.printNumber(); 

    --z3; // 20, -4

    cout << "\n--Pre-Fixado:\n";
    z3.printNumber(); 


    z3++; // 21, -3
    cout << "\n++Pos-Fixado:\n";
    z3.printNumber(); 
    
    (z3++).printNumber();  

    z3.printNumber();

    z3--;
    cout << "\n--Pos-Fixado:\n";
    z3.printNumber(); 
    
    (z3--).printNumber();

    return 0;
}