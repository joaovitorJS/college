#ifndef COMPLEXNUMBERS_H
#define COMPLEXNUMBERS_H

#include <iostream>

class ComplexNumbers
{
private:
    float real; // Parte real
    float imaginary; // Parte imaginaria
public:
    ComplexNumbers();
    ComplexNumbers(float, float);

    void setNumber(float, float);

    float getReal();
    float getImaginary();
    
    ComplexNumbers operator+(ComplexNumbers);
    ComplexNumbers operator-(ComplexNumbers);
    ComplexNumbers operator/(ComplexNumbers);
    ComplexNumbers operator*(ComplexNumbers);
    void operator=(ComplexNumbers);

    bool operator==(ComplexNumbers);
    bool operator!=(ComplexNumbers);

    //pre-fixados
    void operator++();
    void operator--();

    //pos-fixados
    ComplexNumbers operator++(int);
    ComplexNumbers operator--(int);

    void printNumber();

    ~ComplexNumbers();
};


#endif //COMPLEXNUMBERS_H