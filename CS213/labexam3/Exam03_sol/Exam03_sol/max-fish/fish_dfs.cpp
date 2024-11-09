#include <vector>
using namespace std;

class Solution
{
public:
    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0)
        {
            return 0;
        }

        int fish = grid[i][j];

        grid[i][j] = 0;

        fish += dfs(grid, i + 1, j); // down
        fish += dfs(grid, i - 1, j); // up
        fish += dfs(grid, i, j + 1); // right
        fish += dfs(grid, i, j - 1); // left

        return fish;
    }

    int findMaxFish(vector<vector<int>> &grid)
    {
        int maxFish = 0;
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                if (grid[i][j] > 0)
                {
                    maxFish = max(maxFish, dfs(grid, i, j));
                }
            }
        }

        return maxFish;
    }
};