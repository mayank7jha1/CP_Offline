#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
    int N, M;

    // DP tables
    vector<vector<long long>> memoMax;
    vector<vector<long long>> memoMin;
    vector<vector<bool>> visited;

    pair<long long, long long> dfs(int i, int j, const vector<vector<int>>& grid) {
        // Base case
        if (i == N - 1 && j == M - 1) {
            return {grid[i][j], grid[i][j]};
        }

        if (visited[i][j]) {
            return {memoMin[i][j], memoMax[i][j]};
        }

        long long current_val = grid[i][j];

        // Use explicitly typed large long long constants instead of 1e18 (which is a double)
        long long min_prod = 1e18;
        long long max_prod = -1e18;

        // Try going DOWN
        if (i + 1 < N) {
            // Replaced C++17 structured binding with standard C++11 pair
            pair<long long, long long> down_res = dfs(i + 1, j, grid);

            long long p1 = current_val * down_res.first;
            long long p2 = current_val * down_res.second;

            // Nested min/max is universally supported across all C++ versions
            min_prod = min(min_prod, min(p1, p2));
            max_prod = max(max_prod, max(p1, p2));
        }

        // Try going RIGHT
        if (j + 1 < M) {
            pair<long long, long long> right_res = dfs(i, j + 1, grid);

            long long p1 = current_val * right_res.first;
            long long p2 = current_val * right_res.second;

            min_prod = min(min_prod, min(p1, p2));
            max_prod = max(max_prod, max(p1, p2));
        }

        visited[i][j] = true;
        memoMin[i][j] = min_prod;
        memoMax[i][j] = max_prod;

        return {min_prod, max_prod};
    }

public:
    int maxProductPath(vector<vector<int>>& grid) {
        N = grid.size();
        M = grid[0].size();

        memoMax.assign(N, vector<long long>(M, 0));
        memoMin.assign(N, vector<long long>(M, 0));
        visited.assign(N, vector<bool>(M, false));

        pair<long long, long long> result = dfs(0, 0, grid);

        if (result.second < 0) {
            return -1;
        }

        // Apply modulo exactly once at the very end
        return result.second % 1000000007;
    }
};
