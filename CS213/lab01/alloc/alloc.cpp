#include <iostream>
#include <map>
#include <vector>
#include "rdtsc.h"

// Let's consider vectors again. When a vector is declared without specifying
// a size, it starts empty. However, there needs to be some initial allocation
// of space in anticipation of new elements being added. As we begin filling
// the vector, there will come a point when the allocated memory runs out.
// At this stage, the vector needs to allocate more memory. Your task is to
// write code that detects at what size the new allocation occurs and determine
// the amount of extra memory being allocated.

// Hint: Keep in mind that when a vector requires more memory, it not only
//   needs additional space but also needs to be relocated to ensure continuous
//   storage of the vector. This relocation process takes some time to execute.

void time_graph(size_t N){
  //Shows to positions where it takes more time, suggesting these can be the places where the vector is relocating itself
  ClockCounter time;

  std::vector<int> a;
  for (int i = 0; i < N; i++)
  {
    time.start();
    a.push_back(i);
    double t = (double)time.stop();
    std::cout << i << " " << t <<"\n";
  }
}

void position_graph(size_t N){
  //Shows the difference between the starting position of vector and position of curretly added element, a change in slope suggests these can be the positions where the vector is relocating itself
  std::vector<int> a;
  std::vector<int>::iterator base;
  for (int i = 0; i < N; i++)
  {
    a.push_back(i);
    if (i==0){base =  a.begin();}
    std::cout << i << " " << a.end() - base << "\n";
  }
  
}

int main() {
  /* std::cout << "0 0\n"; // Dumping dummy data such that
  std::cout << "1 1\n"; // GNUplot does not complain
   */

  size_t N = 10000;
  time_graph(N);
  
  return 0;
}
