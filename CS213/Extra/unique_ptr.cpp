// The unique_ptr is a smart pointer that retains exclusive ownership of an object through a pointer.
// It ensures that only one unique_ptr instance can own the object at a time.
// When the unique_ptr is destroyed, the object is also destroyed.
//
// Properties of unique_ptr:
// 1. Exclusive ownership: Only one unique_ptr instance can own the object.
// 2. Automatic destruction: When the unique_ptr is destroyed, the object is also destroyed.
// 3. No ownership transfer: unique_ptr does not transfer ownership of the object.
// 4. No copy or assignment: unique_ptr instances cannot be copied or assigned to another unique_ptr.
//
// Example usage:
//
// #include <iostream>
// #include <memory>
//
// int main() {
//     std::unique_ptr<int> ptr1(new int(10)); // Create a unique_ptr and allocate an integer
//     std::unique_ptr<int> ptr2 = std::make_unique<int>(20); // Create a unique_ptr using make_unique
//
//     std::cout << "ptr1 value: " << *ptr1 << std::endl; // Output: ptr1 value: 10
//     std::cout << "ptr2 value: " << *ptr2 << std::endl; // Output: ptr2 value: 20
//
//     ptr1.reset(); // Release ownership of the object
//
//     if (ptr1) { // Check if ptr1 is not null
//         std::cout << "ptr1 is not null" << std::endl;
//     } else {
//         std::cout << "ptr1 is null" << std::endl; // Output: ptr1 is null
//     }
//
//     return 0;
// }

#include <iostream>
#include <memory>
int main(){
    int c = 14;
    {//Remove the curly braces, get c out of the scope and the function will run without errors in executable
        int * b = &c;
        std::unique_ptr<int> a (b);
        std::cout<<*a<<std::endl;
        std::cout<<*b<<std::endl;
        std::cout << "beep" <<std::endl;
    }
    std::cout << "wtf" <<std::endl;

    int d = 56;
    std::unique_ptr<int> e = std::make_unique<int>(d);
    std::cout << "hi" <<std::endl;
    std::cout << *e <<std::endl;
    std::cout << "there" <<std::endl;
    std::cout << c <<std::endl;
}

