#include <iostream>
using namespace std;
int main(){
    int a = 5;//s0
    int b = 3;//s1
    bool result;
    if (a>b){
        if (a%b == 0){
            result = 1;
        }
        else{
            result = 0;
        }
    }
    else{
        if (b%a == 0){
            result = 1;
        }
        else{
            result = 0;
        }
    }
}