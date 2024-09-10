// The weak_ptr is a smart pointer that holds a non-owning reference to an object managed by shared_ptr.
// It is used to break circular references and prevent memory leaks.
//
// Properties of weak_ptr:
// 1. Non-owning reference: weak_ptr does not own the object and does not increase its reference count.
// 2. Expiring reference: weak_ptr can become expired if the last shared_ptr pointing to the object is destroyed.
// 3. Dereferencing: weak_ptr can be dereferenced only if it is not expired.
// 4. Converting to shared_ptr: weak_ptr can be converted to shared_ptr if it is not expired.
//
// Example usage:
//
#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> ptr1(new int(10)); // Create a shared_ptr and allocate an integer
    std::weak_ptr<int> ptr2 = ptr1; // ptr2 holds a weak reference to ptr1
    std::cout << "ptr1 count: " << ptr1.use_count() << std::endl; // Output: ptr1 count: 1
    std::cout << "ptr2 count: " << ptr2.use_count() << std::endl; // Output: ptr2 count: 1
    ptr1.reset(); // Release ownership of the object
    std::cout << "ptr1 count after reset: " << ptr1.use_count() << std::endl; // Output: ptr1 count after reset: 0
    std::cout << "ptr2 count after reset: " << ptr2.use_count() << std::endl; // Output: ptr2 count after reset: 0
    if (auto sharedPtr = ptr2.lock()) { // Check if ptr2 is not expired
        std::cout << "ptr2 is not expired, value: " << *sharedPtr << std::endl; // Output: ptr2 is not expired, value: 10
    } else {
        std::cout << "ptr2 is expired" << std::endl;
    }
    return 0;
}
