#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    ////////////////////////////////////////////////////////////////////////////

    // You can add more functions here

    int bfs(vector<vector<int>> &grid,vector<vector<int>> &viewed, int i ,int j){
      queue<pair<int,int>> todo;
      todo.push(make_pair(i,j));
      int res=0;
      while (!todo.empty()){
        int a= todo.front().first;int b = todo.front().second; todo.pop();

        vector<pair<int,int>> neighbours {make_pair(a+1,b),make_pair(a-1,b),make_pair(a,b-1),make_pair(a,b+1)};
        for (auto n: neighbours){
          if (n.first >= grid.size() or n.second >= grid[0].size() or n.first <0 or n.second <0) continue;
          else if (grid[n.first][n.second] == 0 or viewed[n.first][n.second] != 0) continue;
          else{
            viewed[n.first][n.second] = 1;
            res += grid[n.first][n.second];
            todo.push(n);
          }
        }
      }
      return res;
    }

    ////////////////////////////////////////////////////////////////////////////

    // Write your code inside the findMaxFish function
    int findMaxFish(vector<vector<int>> &grid)
    {
      int y = grid.size();
      int x = grid[0].size();

      vector<vector<int>> viewed(y, vector<int>(x,0));
      //vector<vector<int>> viewed{grid};
      //viewed.clear();
      
      int max_fish = 0;

      for (int i = 0; i<y;i++){
        for (int j = 0; j < x; j++){
          if (!viewed[i][j]){
            max_fish = max(max_fish,bfs(grid,viewed,i,j));
          }
        }
      }

      return max_fish;
    }
};
