#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv) {

  if( argc < 2 ) {
    cout<<"Give a sequence of paranthesses!\n"
        <<endl;
    return 1;
  }
  char* s = new char[100];
  s = argv[1];
  int matched_length = 0;
  int a,b,c,d;
  char g[] = "()";
  d = int(g[0]);
  c = int(g[1]);
  int n = strlen(s);

  for (int i = 0; i < n - 1 ; i++){
    a = int(s[i]);
    b = int(s[i+1]);
    if(a == d && b == c) {
      matched_length += 2;
    }
  }

  cout << s << " " << matched_length <<  endl;
  //delete[] s;
}
