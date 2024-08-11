#include <iostream>
using namespace std;
int main(){
    foo(4);
}
int foo (int x ) {
try {
throw 20; // something has gone wrong !!
}
catch ( auto e ){ // type of e is matched !
    cout << "An int exception occurred . " << e << ’\n’;
}
return 0;
}