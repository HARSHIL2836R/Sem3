#include <cstdlib>
#include <cstddef>
#pragma once

/*
 * You must NOT add ANY other includes than this.
 * The purpose of this file is to implement the functioning of a stack in C++.
 * Implement all the method functions in this file, your way.
 * Ensure that ALL of them are on average constant time. Amortized O(1) is OK.
 * You must NOT change the method signature of any of the methods.
 * You may add any additional methods or data members as you need.
 * Those methods and data members should be protected.
 */

template <typename T>
class Stack {
    // ADD ANY ADDITIONAL DATA MEMBERS OR METHODS HERE
    int *A;//pointer to array used to make stack
    size_t N = 2;//The capacity of the stack
    int h = -1;//current head of stack
    // DO NOT CHANGE THE METHOD SIGNATURES BELOW
public:
    Stack();
    ~Stack();
    void push(T value);
    T pop();
    T peek();
    bool isEmpty();
    size_t getSize();
protected:
    void expand(){//in exponential growth, the average cost of push remains O(1)
        N *= 2;
        int* A_new = new T[N];
        for (int i = 0; i < N/2; i++)
        {
            A_new[i]=A[i];
        }
        delete [] A;
        A = A_new;
    };
};

// ENTER YOUR IMPLEMENTATIONS OF METHODS BELOW

template <typename T> Stack<T> :: Stack(){//Don't specify return type on constructors
    A = new T[N];
    h++;
}
template <typename T> Stack<T> :: ~Stack(){
    delete [] A;
}
template <typename T> void Stack<T> :: push(T value){
    if (getSize() == N){
        expand();
    }
    A[++h]=value;
}
template <typename T> T Stack<T> :: pop(){
    return A[head--];
}
template <typename T> T Stack<T> :: peek(){
    return A[head];
}
template <typename T> bool Stack<T> :: isEmpty(){
    return (getSize() == 0);
}
template <typename T> size_t Stack<T> :: getSize(){
    return h;
}
