#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    int bfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (grid[i][j] == 0)
        {
            return 0;
        }

        int totalFish = 0;
        queue<pair<int, int>> q;
        q.push({i, j});

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (grid[x][y] > 0)
            {
                totalFish += grid[x][y];
                grid[x][y] = 0;
            }

            for (const auto &dir : directions)
            {
                int newX = x + dir.first;
                int newY = y + dir.second;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] > 0)
                {
                    q.push({newX, newY});
                }
            }
        }

        return totalFish;
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
                    maxFish = max(maxFish, bfs(grid, i, j));
                }
            }
        }

        return maxFish;
    }
};
