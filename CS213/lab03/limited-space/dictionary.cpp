#include "dictionary.h"
#include <cmath>

// ------------------------------------------------
//  IMPORTANT
// ------------------------------------------------
// You must have written dictionary.cpp for earlier problem.
// You need to use the code here again. However, there is
// a type difference in this problem. The key is a string not array.
// Please modify your code as you need.

Dictionary::Dictionary(){
  // (ALMOST) COPY from the earlier dictionary problem
    A = new Entry[N];
    for (int i = 0; i < N; i++){
        A[i].key="";
        A->tomb = 0;
    }
};


int Dictionary::hashValue(std::string key){
  // (ALMOST) COPY from the earlier dictionary problem
    int hashValue = 0;
    // compute hash
    int p =33;
    long double multiplier = (sqrtl(5)-1)/2;//initially A
    long double encoding = 0;//We're using 64 bits because the fractional part also supports 64 bits only, however the value of largest power in the polynomial can reach nearly to 2^170
    int i = 0;
    while (key[i] != '\0' && i<32){
        encoding += key[i]*multiplier;
        multiplier *= p;
        multiplier -= floor(multiplier);
        i++;
    }
    //encoding = encoding % int(1/A);//Reduce overflow when multiplying with A
    encoding -= floor(encoding);
    hashValue = N*encoding;
    return hashValue;
}

int Dictionary::findFreeIndex(std::string key){
  // (ALMOST) COPY from the earlier dictionary problem
  int index = hashValue(key);
    int initial_index = index;
    while (A[index].key != ""){
        index = (index + 1) % N;
        if (index == initial_index){
            return -1;
        }
    }
    return index;
}

struct Entry* Dictionary::get(std::string key){
  // (ALMOST) COPY from the earlier dictionary problem
  int index = hashValue(key);
    int initial_index = index;

    while (A[index].key != key){
        index=(index +1)%N;
        if (index == initial_index || A[index].key == ""){
            return NULL;
        }
    }
    return &A[index];
}

bool Dictionary::put(Entry e){
  // (ALMOST) COPY from the earlier dictionary problem
    int index = findFreeIndex(e.key);
    if (index == -1){
        return false;
    }
    A[index] = e;
    return true;
}

bool Dictionary::remove(std::string key){
  // (ALMOST) COPY from the earlier dictionary problem
    Entry *e = get(key);
    if (e == NULL){
        return false;
    }
    e->key = "~";
    e->tomb = 1;
    return true;
}
