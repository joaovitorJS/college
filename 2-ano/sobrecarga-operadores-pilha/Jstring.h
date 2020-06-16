#ifndef JSTRING_H
#define JSTRING_H

#include <iostream>
#include <string.h>

using namespace std;

class Jstring
{
private:
    char str[77];
public:
    Jstring();
    Jstring(const char*);

    void setStr(const char*);
    char* getStr();

    void concat(Jstring);
    void copy(Jstring);

    Jstring operator+(Jstring);
    char& operator[](int);
    
 
    ~Jstring();
};


#endif //JSTRING_H