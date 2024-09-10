// The shared_ptr is a smart pointer that retains shared ownership of an object through a pointer.
// It is similar to unique_ptr but allows multiple shared_ptr instances to own the same object.
// When the last shared_ptr pointing to an object is destroyed, the object is also destroyed.
//
// Properties of shared_ptr:
// 1. Shared ownership: Multiple shared_ptr instances can own the same object.
// 2. Reference counting: shared_ptr keeps track of the number of shared_ptr instances pointing to the object.
// 3. Automatic destruction: When the last shared_ptr pointing to an object is destroyed, the object is also destroyed.
// 4. Thread-safe: shared_ptr is thread-safe and can be used in multi-threaded environments.
// 5. No ownership transfer: shared_ptr does not transfer ownership of the object.
//
// Example usage:
#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> ptr1(new int(10)); // Create a shared_ptr and allocate an integer
    std::shared_ptr<int> ptr2 = ptr1; // ptr2 shares ownership with ptr1
    std::cout << "ptr1 count: " << ptr1.use_count() << std::endl; // Output: ptr1 count: 2
    std::cout << "ptr2 count: " << ptr2.use_count() << std::endl; // Output: ptr2 count: 2
    ptr1.reset(); // Release ownership of the object
    std::cout << "ptr1 count after reset: " << ptr1.use_count() << std::endl; // Output: ptr1 count after reset: 0
    std::cout << "ptr2 count after reset: " << ptr2.use_count() << std::endl; // Output: ptr2 count after reset: 1
    return 0;
}