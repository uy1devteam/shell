#include <iostream>
#include "header.h"
using namespace std;

int main(int argc, char**argv){
    if(argc == 2){
        long n = conver( argv[1]);
        cout << fibo(n, 1l, 2l) << endl;
    }
    return 0;
}