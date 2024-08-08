#include <iostream>
using namespace std;

class MyClass
{
private:
    int counter;
    mutable int mcounter;//can be changed even in a const method
public:
    MyClass(): counter(0), mcounter(0) {}
    void Foo()
    { 
        std::cout << "Foo" << std::endl;
    }

    void Foo() const
    {//constant type method
        std::cout << "Foo const" << std::endl;
    }
    void Example() const
    {
        //counter++; //Shows error: 'Expression must be modifiable lvalue' if uncommented
        mcounter++;//No error as it is a mutable member
        Foo();
    }
    void CExample()
    {
        counter++;//valid
        Foo();//const functions can be called
    }
};

int main(){
    MyClass obj;//non-const objects can call any type of functions
    MyClass const const_obj;//const object can only call const functions to maintain consistency

    const_obj.Foo();//const object calls const function: Foo const
    obj.Foo();//non-const object calls non-const function: Foo
    //const_obj.CExample();//Shows error 'the object has type qualifiers that are not compatible with the member function "MyClass::CExample"' when uncommented
    obj.Example();//const member calls const member: Foo const
    obj.CExample();//non-cost member calls non-const member: Foo
}