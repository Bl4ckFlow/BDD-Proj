#include <iostream>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

class Account{
    public : 
        string name;
        int AccessibiliyLvl;
        Account* Next;
        Account(string name);
        Account(string name, int AccessibiliyLvl);
};

Account::Account(string name){
    this->name=name;
    this->AccessibiliyLvl = 0;
    Next = nullptr;
}

Account::Account(string name, int AccessibiliyLvl){
    this->name=name;
    this->AccessibiliyLvl = AccessibiliyLvl;
    Next = nullptr;
}