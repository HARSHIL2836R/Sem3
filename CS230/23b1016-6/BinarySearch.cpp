#include <iostream>
using namespace std;

int binarySearch(int *A, int len, int start, int end, int val){
    if (start > end) return -1;
    int mid = start + (end - start)/2;
    if (A[mid] == val) return mid;
    if (A[mid] > val) return binarySearch(A,len,start,mid-1, val);
    if (A[mid] < val) return binarySearch(A,len,mid+1,end,val);
}
int main(){
    int len = 3;
    int arr[len];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    int el;
    cin>>el;
    cout<<binarySearch(arr,len,0,len,el);
}
