#include <iostream>
#include "Jstring.h"

using namespace std;

int main() {

    Jstring s1("str1"), s2("str2"), s3;
    

    s3 = s1 + s2;
    
    cout << s1.getStr() << " + " << s2.getStr() << " = " << s3.getStr() << endl;

    cout << s3[2] << endl;

    cout << s3.getStr() << endl;

    s3[2] = 'f';

    cout << s3.getStr() << endl;
    
    return 0;
}