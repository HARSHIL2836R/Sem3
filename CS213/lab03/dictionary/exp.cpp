#include <iostream>
using namespace std;
struct my_strcut{
    char* key;
    int val;
};
int main(){
    my_strcut empty;
    empty.val = -1;
    my_strcut *A = new my_strcut[3];
    cout<<A[0].val<<endl<<"hi"<<endl;
    for (int i = 0; i < 10 && i != 5; i++)
    {
        cout<<i;
    }
    
}