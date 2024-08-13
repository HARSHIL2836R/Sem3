#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return (tail-head)==0; // dummy return
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return tail == N-1; // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
  N=nextSize();
  T * A_new = new T[N];
  int i = 0;
  while (head != tail)
  {
    A_new[i] = A[head];
    head++;
    i++;
  }
  head = 0;
  tail = i-1;
  delete [] A;
  A = A_new;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (tail-head); // dummy return
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if (isFull()){
    grow();
  }
  A[++tail]=x;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if (isEmpty()){
    return false;
  }
  else{
    A[head++]=NULL;
    return true;
  }
}
