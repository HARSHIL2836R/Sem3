#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
-- Print will not work until you have a good printing function
*/


#include "heap.h"

int Heap::parent(int i) {
  return (i-1)/2;
}

int Heap::left(int i) {
  return 2*i+1;
}

int Heap::right(int i) {
  return 2*i+2;
}

int Heap::max() {
  return store[0];
}

void Heap::swap(int i, int j) {
  iter_swap(store.begin()+i,store.begin()+j);
  swap_count++;
}

void Heap::insert(int v) {
  int i = store.size(); 
  store.push_back(v);
  sz++;
  while (i > 0 && store[parent(i)] > store[i]){
    swap(parent(i), i);
    i = parent(i);
  }
}

void Heap::heapify(int i) {
  int c = i;
  if (right(i) < sz && store[i] < store[right(i)] && store[right(i)] > store[left(i)]){
    c = right(i);
  }
  else if (left(i) < sz && store[i] < store[left(i)]){
    c = left(i);
  }
  if (c == i){
    return;
  }
  swap(c,i);
  heapify(c);
}


void Heap::deleteMax() {
  swap(0, sz-1);
  sz--;
  heapify(0);
}

void Heap::buildHeap() {
  sz = store.size();
  for (int i = sz-1; i >= 0; i--){
    heapify(i);
  }
}

void Heap::heapSort() {
  sz = store.size();
  buildHeap();
  while (sz > 0){
    if (sz == 3){
      int a = 1;
    }
    deleteMax();
  }
}


