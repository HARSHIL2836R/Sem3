#include <iostream>
#include <memory>
#include <vector>
#include <string.h>
#pragma once

/* You should NOT add ANY other includes in this file.
 * Do NOT add `using namespace std` in header files. It is a bad practice.
 * Do not panic on seeing `value_type`, `size_type`, `reference` etc.
 * They are just placeholders. You can replace them with actual types
 * but it is recommended to keep them as is.
 * The purpose of all this is to introduce you to more of C++ syntax.
 *
 * Your task is to implement the class `Heap` and all its methods.
 * You should not change the class definition or ANY of its PUBLIC functions.
 * You are free to add any members (should be PROTECTED) to the class.
 * You can also add PROTECTED member function signatures to the class.
 * But those should be implemented below, OUTSIDE the class definition.
 *
 * A quick intro to comparator classes in C++:
 * a class object `comp` of type `Compare` can be used to compare two values
 * like this: `comp(a, b)`. It returns `true` if `a` is less than `b` and
 * the comparator is a `std::less` object. If the comparator is a `std::greater`
 * object, it returns `true` if `a` is greater than `b`.
 * Assuming that the comparator is a `std::less` object, your implementation
 * should be that of a MIN-HEAP (top = smallest element).
 * You can create a comparator object like this: `Compare comp;`.
 *
 * A quick intro to std::move in C++:
 * `std::move` is used to convert a variable to an rvalue reference.
 * It is used to transfer ownership of a resource from one object to another.
 * For example, `b = std::move(a)` transfers the ownership of `a` to `b`.
 * After that, `a` should not be used anywhere in the code.
 * It is used in move constructors and move assignment operators.
 * That is, the ones with `heap_t&& other` as a parameter.
 * the `noexcept` keyword is used to specify that a function 
 * does not throw any exceptions and is used for optimization purposes.
 *
 * Note that your task involves completing this class as well as
 * complete the tasks in files "student.h" and "merge-sorted-lists.h".
 */

template <typename T, class Compare = std::less<T>>
class heap_t {
    // Do not modify any existing members of this class.
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;

public:
    heap_t();
    ~heap_t();
    heap_t(const heap_t& other);
    heap_t(heap_t&& other) noexcept;
    heap_t& operator = (const heap_t& other);
    heap_t& operator = (heap_t&& other) noexcept;

    void push(const value_type& value);
    value_type pop();
    const_reference top() const;
    size_type size() const;
    bool empty() const;
    void clear();

protected:
    std::vector<value_type> data;
    // TODO: Add you data members and helper functions here.
    size_type sz = 0;

    // heap Navigation
    int parent(int);
    int left(int);
    int right(int);

    // Heap interface
    void swap(int i, int j);
    int max();          // read max
    void insert(const value_type& value); // insert key in heap
    void heapify(int i);// heapify a node
    void deleteMax();   // deletes max
    void buildHeap();   // builds heap
    void heapSort();    // sorts conentens of heap and does not physically delete
                        // the content

    void print(int i=0, const std::string& prefix="", bool isLeft=false);
    // End TODO
};

// TODO: Implement the class methods here.

template <typename T, class Compare>
heap_t<T, Compare>::heap_t() {
  
}

template <typename T, class Compare>
heap_t<T, Compare>::~heap_t() {
  delete &data;
}

template <typename T, class Compare>
heap_t<T, Compare>::heap_t(const heap_t& other) {
  data = vector(other);
}

template <typename T, class Compare>
heap_t<T, Compare>::heap_t(heap_t&& other) noexcept {
  data = vector(other);
}

template <typename T, class Compare>
heap_t<T, Compare>& heap_t<T, Compare>::operator = (const heap_t& other) {
  data = other.data;
  return *this;
}

template <typename T, class Compare>
heap_t<T, Compare>& heap_t<T, Compare>::operator = (heap_t&& other) noexcept {
    data = std::move(other.data);
    return *this;
}

template <typename T, class Compare>
void heap_t<T, Compare>::push(const value_type& value) {
  insert(value);
}

template <typename T, class Compare>
typename heap_t<T, Compare>::value_type heap_t<T, Compare>::pop() {
    if (data.size() == 0) {
        throw std::out_of_range("Heap is empty");
    }
    value_type top = data[0];
    deleteMax();
    return top;
}

template <typename T, class Compare>
typename heap_t<T, Compare>::const_reference heap_t<T, Compare>::top() const {
    if (data.size() == 0) {
        throw std::out_of_range("Heap is empty");
    }
    return data[0];
}

template <typename T, class Compare>
typename heap_t<T, Compare>::size_type heap_t<T, Compare>::size() const {
  return sz;
}

template <typename T, class Compare>
bool heap_t<T, Compare>::empty() const {
  return sz == 0;
}

template <typename T, class Compare>
void heap_t<T, Compare>::clear() {
  data.clear();
  sz = 0;
}

// End TODO

//HELPER FUNCTIONS
template <typename T, class Compare>
int heap_t<T,Compare>::parent(int i) {
  return (i-1)/2;
}

template <typename T, class Compare>
int heap_t<T,Compare>::left(int i) {
  return 2*i+1;
}

template <typename T, class Compare>
int heap_t<T,Compare>::right(int i) {
  return 2*i+2;
}

template <typename T, class Compare>
int heap_t<T,Compare>::max() {
  return data[0];
}

template <typename T, class Compare>
void heap_t<T,Compare>::swap(int i, int j) {
  iter_swap(data.begin()+i,data.begin()+j);
}

template <typename T, class Compare>
void heap_t<T,Compare>::insert(const value_type& value) {
  int i = data.size(); 
  data.push_back(value);
  sz++;
  while (i > 0 && data[parent(i)] > data[i]){
    swap(parent(i), i);
    i = parent(i);
  }
}

template <typename T, class Compare>
void heap_t<T,Compare>::heapify(int i) {
  int c = i;
  if (right(i) < sz && data[i] < data[right(i)] && data[right(i)] > data[left(i)]){
    c = right(i);
  }
  else if (left(i) < sz && data[i] < data[left(i)]){
    c = left(i);
  }
  if (c == i){
    return;
  }
  swap(c,i);
  heapify(c);
}


template <typename T, class Compare>
void heap_t<T,Compare>::deleteMax() {
  swap(0, sz-1);
  sz--;
  heapify(0);
}

template <typename T, class Compare>
void heap_t<T,Compare>::buildHeap() {
  sz = data.size();
  for (int i = sz-1; i >= 0; i--){
    heapify(i);
  }
}

template <typename T, class Compare>
void heap_t<T,Compare>::heapSort() {
  sz = data.size();
  buildHeap();
  while (sz > 0){
    if (sz == 3){
      int a = 1;
    }
    deleteMax();
  }
}

/*template <typename T, class Compare>
inline void heap_t<T,Compare>::print(int i, const std::string& prefix, bool isLeft)
{
    if( size() > i && i >= 0 )
    {
      std::cout << prefix << (isLeft ? "|--" : "|__" ) << std::__atomic_impl::store[i] << std::endl;
      // enter the next tree level - left and right branch
      print( left(i), prefix + (isLeft ? "│   " : "    "), true);
      print( right(i), prefix + (isLeft ? "│   " : "    "), false);
    }
}*/