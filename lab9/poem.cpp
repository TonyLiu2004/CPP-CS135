/**
Author: Tony Liu
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Lab 9 D

Keeps creating poems with dynamic memory allocation
**/
#include <iostream>
using namespace std;

string * createAPoemDynamically() {
    string *p = new string;
    *p = "Roses are red, violets are blue";
    return p;
}

int main() {
    while(true) {
        string *p;
        p = createAPoemDynamically();
        cout << *p << endl;
        // assume that the poem p is not needed at this point
        delete p;
    }
}