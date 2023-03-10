/*
Author: Tony Liu
Course: CSCI-135
Instructor: Genady Maryash
Assignment: E5.15

input three  integers into sort3() to order them by which integer 
is larger. sort3 directly changes the integers.
*/
#include <iostream>

void sort2(int&, int&);
void sort3(int&, int&, int&);
int main(){
    int a = 3;
    int b = 2;
    int c = 12;
    sort3(a,b,c);
    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}

void sort2(int& a, int& b){
    if(a>b){
        int t = a;
        a = b;
        b = t;
    }
}

void sort3(int& a, int& b, int& c){
    sort2(a,b);
    sort2(b,c);
    sort2(a,b);
}