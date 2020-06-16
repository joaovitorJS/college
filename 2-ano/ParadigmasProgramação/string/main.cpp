#include <iostream>
#include "Jstring.h"

using namespace std;

int main() {

    Jstring s1, s2("str2");

    s2.copy(s1);

    s1.setStr("str1");
    s2.setStr("str2");

    s1.concat(s2);
    s2.copy(s1);

    cout << s1.getStr() << s2.getStr() << endl;

    return 0;
}