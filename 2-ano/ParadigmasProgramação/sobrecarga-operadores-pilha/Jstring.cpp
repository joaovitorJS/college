#include "Jstring.h"

Jstring::Jstring() {
    setStr(" ");
}

Jstring::Jstring(const char* str) {
    setStr(str);
}

void Jstring::setStr(const char* str) {
    strcpy(this->str, str);
}

char* Jstring::getStr() {
    return this->str;
}

void Jstring::concat(Jstring str) {
    strcat(this->str, str.getStr());
}

void Jstring::copy(Jstring str) {
    strcpy(this->str, str.getStr());
}

Jstring Jstring::operator+(Jstring obj) {
    Jstring temp(this->str);

    strcat(temp.str, obj.str);    

    return temp;
}

char& Jstring::operator[](int index) {
    if (index >= 0 && index < 77 ) {
        return this->str[index];
    } 
}

Jstring::~Jstring() {}