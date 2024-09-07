#include "min-max-queue.h"

/*
The task of this question is to implement a Min Max Queue, a queue
data structure that can find the minimum/maximum of ALL
the elements CURRENTLY PRESENT in it in O(1)/amortized O(1) time.
The queue should also be able to push/pop in amortized O(1) time.
Checking front/empty should also be O(1) time.

In min-max-queue.cpp, complete the function definitions
(You may leave the constructor/destructor empty if not needed).
Feel free to add any member variables/functions to this class or
any new class/struct(s) if needed. There are brief descriptions
for the given functions as well.

Constraints:
 - 0 <= n <= 10^7 (or 10 million) where n are the number of
   elements pushed/popped from queue.
 - Only non-negative integers (any from 0 to 2^31-1) will be
   pushed into the queue.

2 public testcases have been given to you (one for small n and other
for large). There will be some hidden testcases as well.
Your grading will depend on the output obtained from the hidden
testcases ONLY and NOT the 2 public ones.

"min-max-queue.cpp" shall ONLY be considered for grading (Don't put your solution in any other file).
DON'T TOUCH "main.cpp" or any ".h" file.

NOTE: NO OTHER "#include"s are allowed. Straight 0 if did.

During grading, a time limit will be set for the execution on the
testcases. If the functions are implemented in O(1)/amortized O(1)
time, then you don't need to worry about the time limit, they won't
exceed it. (Long testcase may take few seconds).

More efficient implementations will get greater marks!!

In case of the queue is empty, return INT_MAX for getMin(),
return INT_MIN for getMax() and return -1 for front().

*/


class MinMaxQueue {
private:
  // Add your fields here!!
  stack<int> sck;
  stack<int> max_his;//Contains all previous max elements
  stack<int> min_his;//Contains all previous minimum elements

public:
  MinMaxQueue() {
    max_his.push(INT_MIN);
    min_his.push(INT_MAX);
  }

  void push(int n) {
    
    sck.push(n);
    if (sck.empty() || n>=max_his.top()){
      max_his.push(n);
    }
    if (sck.empty() || n<=min_his.top()){
      min_his.push(n);
    }
  }

  void pop() {
    stack<int> new_sck;
    while(!sck.empty()){
      new_sck.push(sck.top());
      sck.pop();
    }
    new_sck.pop();
    if (new_sck.top() == max_his.top()){
      max_his.pop();
    }
    if (new_sck.top() == min_his.top()){
      min_his.pop();
    }
    while(!new_sck.empty()){
      sck.push(new_sck.top());
      new_sck.pop();
    }
  }

  int front() {
    if (sck.empty()){
      return -1;
    }
    return sck.top();
  }

  int getMin() {
    if (sck.empty()){
      return INT_MAX;
    }
    else{
      return min_his.top();
    }
  }

  int getMax() {
    if (sck.empty()){
      return INT_MIN;
    }
    else{
      return max_his.top();
    }
  }

  bool empty() {
    return sck.empty();
  }
};
