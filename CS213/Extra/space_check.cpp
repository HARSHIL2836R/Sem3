#include <iostream>
#include <stack>
using namespace std;
int main(){
    stack<int> arr[10];
    arr[0].push(4);
    stack<int> * ptr = &arr[0];
    cout<<arr[0].top();
    stack<int> new_stack;new_stack.push(1);
    arr[0] = new_stack;
    cout<<ptr->top();
}