#include "swap-pairs.h"

using namespace std;

// In this question, you have to reverse the adjacent nodes of a singly linked list.
// The nodes will have only the data and the link of the next node.
// In last node, the link part of the node will be nullptr.
// 'head' is a pointer that holds the address of the first node of the linked list.
// If the linked list is empty or contains one element you don't need to reverse.
// You have to reverse the adjacent nodes and do not swap the values of the adjacent nodes.

// For example:
// If a linked list contains:
// 22 50 17 95 62 31 79 34 53 66 86 87 48 25 4
// The resulting linked list should contain:
// 50 22 95 17 31 62 34 79 66 53 87 86 25 48 4

// For more examples, please look at testcases folder


void reverseAdjacentNodes(Node*& head) {
  Node* curr = head;
  if (curr != nullptr && curr->link != nullptr){
    head = curr->link;
  }
  while (curr != nullptr && curr->link != nullptr){
    Node* next = curr->link;
    if (next->link == nullptr){
      curr->link = nullptr;
      next->link = curr;
      return;
    }
    else if (next->link->link == nullptr){
      curr->link = next->link;
      next->link = curr;
      return;
    }
    else if (next->link->link->link == nullptr)
    {
      curr->link = next->link->link;//1
      next->link->link->link = next->link;//4
      next->link->link = nullptr;//3
      next->link = curr;//2
      return;
    }
    else if (next->link->link->link->link == nullptr){
      Node* fifth = next->link->link->link;//5th node
      curr->link = next->link->link;//1
      next->link->link->link = next->link;//4
      next->link->link = fifth;//3
      next->link = curr;//2
      return;
    }
    else{
      Node* fifth = next->link->link->link;//5th node
      curr->link = next->link->link;//1
      next->link->link->link = next->link;//4
      next->link->link = fifth->link;//3
      next->link = curr;//2
      curr = fifth;
    }
    
  }
  return;
}
