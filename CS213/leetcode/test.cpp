using namespace std;
#include<iostream>
template <class T>
int countzeros (T a[], int size)
{ int count = 0;
for (int i = 0; i < size; i++)
if (a[i] == 0) count ++;
return count;
}