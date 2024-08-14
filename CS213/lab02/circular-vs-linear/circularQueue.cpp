#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return head == tail;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return (N+tail-head)%N == N-1;
}

template <typename T> void DynamicQueue<T> :: grow() {
  N=nextSize();
  T * A_new = new T[N];
  int i = 0;
  while ((N+tail-head)%N != 1)
  {
    A_new[i] = A[head];
    head = (head+1)%N;
    i++;
  }
  head = 0;
  tail = i-1;
  delete [] A;
  A = A_new;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (N+tail-head)%N;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if(isFull()){
    grow();
  }
  tail = (N+tail+1)%N;
  A[tail] = x;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if(isEmpty()){
    return false;
  }
  else{
    //A[head] = NULL;
    head = (N+head+1)%N;
    return true;
  }
}
