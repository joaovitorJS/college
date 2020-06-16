#include "ComplexNumbers.h"

ComplexNumbers::ComplexNumbers(): real(0.0), imaginary(0.0) {}

ComplexNumbers::ComplexNumbers(float rm, float im) {
    real = rm;
    imaginary = im;
}

void ComplexNumbers::setNumber(float rm, float im) {
    real = rm;
    imaginary = im;
}

float ComplexNumbers::getReal() {
    return real;
}

float ComplexNumbers::getImaginary() {
    return imaginary;
}

ComplexNumbers ComplexNumbers::operator+(ComplexNumbers obj) {
    float real, imaginary;

    real = this->real + obj.real;
    imaginary = this->imaginary + obj.imaginary;

    return ComplexNumbers(real, imaginary);
}

ComplexNumbers ComplexNumbers::operator-(ComplexNumbers obj) {
    float real, imaginary;

    real = this->real - obj.real;
    imaginary = this->imaginary - obj.imaginary;

    return ComplexNumbers(real, imaginary);
}

ComplexNumbers ComplexNumbers::operator*(ComplexNumbers obj) {
    float real, imaginary;

    real = this->real*obj.real - this->imaginary*obj.imaginary;
    imaginary = this->real*obj.imaginary + this->imaginary*obj.real;

    return ComplexNumbers(real, imaginary);
}

ComplexNumbers ComplexNumbers::operator/(ComplexNumbers obj) {
    float real, imaginary;

    real = (this->real*obj.real + this->imaginary*obj.imaginary) / (obj.real*obj.real + obj.imaginary*obj.imaginary);
    imaginary = (this->imaginary*obj.real - this->real*obj.imaginary) / (obj.real*obj.real + obj.imaginary*obj.imaginary);

    return ComplexNumbers(real, imaginary);
}

void ComplexNumbers::operator=(ComplexNumbers obj) {
    this->real = obj.real;
    this->imaginary = obj.imaginary;
}

bool ComplexNumbers::operator==(ComplexNumbers obj) {
    if ( (this->real == obj.real) && (this->imaginary == obj.imaginary) ) {
        return true;
    } else {
        return false;
    }
}

bool ComplexNumbers::operator!=(ComplexNumbers obj) {
    if ( (this->real == obj.real) && (this->imaginary == obj.imaginary) ) {
        return false;
    } else {
        return true;
    }
}

//pre-fixado
void ComplexNumbers::operator++() {
    ++this->real;
    ++this->imaginary;

}

void ComplexNumbers::operator--() {
    --this->real;
    --this->imaginary;

}

//pos-fixado
ComplexNumbers ComplexNumbers::operator++(int) {
    ++this->real;
    ++this->imaginary;
    return ComplexNumbers(this->real-1, this->imaginary-1);
}

ComplexNumbers ComplexNumbers::operator--(int) {
    --this->real;
    --this->imaginary;
    return ComplexNumbers(this->real+1, this->imaginary+1);
}

void ComplexNumbers::printNumber() {
    std::cout << "\nReal: " << real << "\tImaginaria: " << imaginary << std::endl; 
}

ComplexNumbers::~ComplexNumbers() {}