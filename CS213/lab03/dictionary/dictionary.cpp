#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary(){
    A = new Entry[N];
    for (int i = 0; i < N; i++){
        //-1 for tombstone
        A[i].key=NULL;
    }
};


int Dictionary::hashValue(char key[]){
    int hashValue = 0;
    // compute hash
    int p =32;
    long double encoding = key[0];//We're using 64 bits because the fractional part also supports 64 bits only, however the value of largest power in the polynomial can reach nearly to 2^170
    long double multiplier = (sqrtl(5)/2)-0.5;//initially A
    int i = 1;
    long double val;
    while (key[i] != NULL && i<p){
        encoding += key[i]*multiplier;
        multiplier *= multiplier;
        multiplier -= floor(multiplier);
        i++;
    }
    //encoding = encoding % int(1/A);//Reduce overflow when multiplying with A
    std::cout<<encoding;
    hashValue = floor(N*(encoding-floor(encoding)));

    return hashValue;
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    while (A[index].key != NULL && index<N){
        index++;
    }
    
    if (index == N){
        return -1;
    }
    else{
        return index;
    }
}

struct Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    int initial_index = index;

    while (A[index].key!=key)
    {
        index=(index +1)%N;
        if (index == initial_index || (A[index].key == NULL && A[index].value == -1)){
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
    e.value = index;
    A[index] = e;
    return true;
}

bool Dictionary::remove(char key[]){
    Entry *e = get(key);
    if (e == NULL){
        return false;
    }
    e->key = NULL;
    e->value = -1;
    return true;
}
