#include <iostream>
#include <set>
#include <map>

int main(){
    std::map<int,int> s;
    std::cout << s.at(3);// Throws exception
    /* terminate called after throwing an instance of 'std::out_of_range'
    what():  map::at
    Aborted (core dumped) */
    std::cout << s[3];// Outputs 0; bad C++, makes out an entry even without us instructing it to
}