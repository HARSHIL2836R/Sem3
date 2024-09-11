#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

class Heap
{
public:
  // global root for the entire tree
  std::vector<int> store;
  unsigned sz = 0;
  int swap_count = 0;
  // Constructor
  Heap() {};

  // store utilities
  int  size();        // returns the size of store
  void reset();       // clears the store
  void removeLast();  // removes the last element in store
  void append(int k); // appends key in store
  void printStore(unsigned len);

  // heap Navigation
  int parent(int);
  int left(int);
  int right(int);

  // Heap interface
  void swap(int i, int j);
  int max();          // read max
  void insert(int k); // insert key in heap
  void heapify(int i);// heapify a node
  void deleteMax();   // deletes max
  void buildHeap();   // builds heap
  void heapSort();    // sorts conentens of heap and does not physically delete
                      // the content

  void print(int i=0, const string& prefix="", bool isLeft=false);

};

inline int Heap::size() {
  return sz;
}

inline void Heap::reset() {
  store.clear();
  sz = 0;
}

inline void Heap::removeLast() {
  sz = sz - 1;
}

inline void Heap::append(int k) {
  if( sz == store.size() )
    store.push_back(k); // expand if more storage is needed!
  else
    store[sz] = k;
  sz = sz + 1;
}

inline void Heap::printStore(unsigned len)
{
  len = len > store.size()? store.size() : len;
  for( unsigned i = 0; i < len; i++ ) {
    cout << store[i] << " ";
  }
  cout << endl;
}

inline void Heap::print(int i, const string& prefix, bool isLeft)
{
    if( size() > i && i >= 0 )
    {
        cout << prefix << (isLeft ? "|--" : "|__" ) << store[i] << endl;
        // enter the next tree level - left and right branch
        print( left(i), prefix + (isLeft ? "│   " : "    "), true);
        print( right(i), prefix + (isLeft ? "│   " : "    "), false);
    }
}

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
  while (i > 0 && store[parent(i)] < store[i]){
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


