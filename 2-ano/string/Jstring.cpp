#include "Jstring.h"

Jstring::Jstring() {
    setStr(" ");
}

Jstring::Jstring(string str) {
    setStr(str);
}

void Jstring::setStr(string str) {
    this->str = str;
}

string Jstring::getStr() {
    return this->str;
}

void Jstring::concat(Jstring obj) {
    string  str = obj.getStr();
    
    this->str += str;
}

void Jstring::copy(Jstring obj) {
        
    this->str = obj.getStr();
}

Jstring::~Jstring() {}