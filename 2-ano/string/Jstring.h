#ifndef JSTRING_H
#define JSTRING_H

#include <iostream>
#include <string.h>

using namespace std;

class Jstring
{
private:
    string str;
public:
    Jstring();
    Jstring(string);

    void setStr(string);
    string getStr();

    void concat(Jstring);
    void copy(Jstring);
 
    ~Jstring();
};


#endif //JSTRING_H