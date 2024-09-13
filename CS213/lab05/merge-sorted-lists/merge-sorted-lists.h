#include "list.h"
#include "heap.h"

/* You should NOT add ANY other includes in this file.
 * Do not add `using namespace std;` in header files as it is a bad practice.
 *
 * Your task is to implement the function `merge_sorted_lists` below.
 * You are given a vector of doubly linked lists. You should return
 * a single doubly linked list which contains all the elements of all
 * the lists in a sorted order, according to comparator `Compare`.
 * It is guaranteed that for any node `a` in the list, if `b` is the next
 * node, then a->data.height <= b->data.height.
 * Read up more on comparators in C++, in file "heap.h".
 * 
 * Note that your task involves completing this function as well as
 * completing the tasks in files "student.h" and "heap.h".
 */

template <typename T, class Compare>
std::shared_ptr<struct list_node_t<T>> merge_sorted_lists(std::vector<std::shared_ptr<struct list_node_t<T>>> lists) {
    // TODO: Write your code here
    heap_t<std::shared_ptr<struct list_node_t<T>>,Compare> hp;
    for (auto i = lists.begin();i<lists.end();i++) {
        hp.push(*i);
    }
    std::shared_ptr<struct list_node_t<T>> root = nullptr;
    std::shared_ptr<struct list_node_t<T>> prev_node = nullptr;

    while(!hp.empty()) {
        if (root == nullptr) {
            root = hp.pop();
            prev_node = root;
            hp.push(root->next);
        }
        prev_node->next = hp.pop();
        prev_node->next->prev = prev_node;
        hp.push(prev_node->next->next);
        prev_node = prev_node->next;
    }

    return root;
    // End TODO
}
