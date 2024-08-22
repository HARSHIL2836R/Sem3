#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary(){
    A = new Entry[N];
    for (int i = 0; i < N; i++){
        A[i].key=NULL;
        A->tomb = 0;
    }
};

int Dictionary::hashValue(char key[]){
    int hashValue = 0;
    // compute hash
    int p =33;
    long double multiplier = (sqrtl(5)-1)/2;//initially A
    long double encoding = 0;//We're using 64 bits because the fractional part also supports 64 bits only, however the value of largest power in the polynomial can reach nearly to 2^170
    int i = 0;
    while (key[i] != NULL && i<32){
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

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    int initial_index = index;
    while (A[index].key != NULL){
        index = (index + 1) % N;
        if (index == initial_index){
            return -1;
        }
    }
    return index;
}

struct Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    int initial_index = index;

    while (strcmp(A[index].key,key) != 0){
        index=(index +1)%N;
        if (index == initial_index || A[index].key == NULL){
            return NULL;
        }
    }
    return &A[index];
}

bool Dictionary::put(Entry e) {
    int index = findFreeIndex(e.key);
    if (index == -1){
        return false;
    }
    A[index] = e;
    return true;
}

bool Dictionary::remove(char key[]){
    Entry *e = get(key);
    if (e == NULL){
        return false;
    }
    e->key = "~";
    e->tomb = 1;
    return true;
}
