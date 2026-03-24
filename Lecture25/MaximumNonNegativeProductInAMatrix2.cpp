#include<bits/stdc++.h>
using namespace std;



#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Use long long to prevent overflow before applying the modulo
        // Initialize with a dummy value
        vector<vector<long long>> maxDp(m, vector<long long>(n));
        vector<vector<long long>> minDp(m, vector<long long>(n));

        maxDp[0][0] = grid[0][0];
        minDp[0][0] = grid[0][0];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                // Initialize current min/max with a value that will be overwritten
                // We use very small/large numbers or simply values from valid neighbors
                long long curMax = -2e18; // Effectively negative infinity
                long long curMin = 2e18;  // Effectively positive infinity

                // Check path coming from above (top neighbor)
                if (i > 0) {
                    long long p1 = maxDp[i - 1][j] * grid[i][j];
                    long long p2 = minDp[i - 1][j] * grid[i][j];
                    curMax = max({curMax, p1, p2});
                    curMin = min({curMin, p1, p2});
                }

                // Check path coming from the left (left neighbor)
                if (j > 0) {
                    long long p1 = maxDp[i][j - 1] * grid[i][j];
                    long long p2 = minDp[i][j - 1] * grid[i][j];
                    curMax = max({curMax, p1, p2});
                    curMin = min({curMin, p1, p2});
                }

                maxDp[i][j] = curMax;
                minDp[i][j] = curMin;
            }
        }

        long long res = maxDp[m - 1][n - 1];

        // If the max product is negative, return -1 as per problem constraints
        if (res < 0) return -1;

        // Standard modulo 10^9 + 7
        return res % 1000000007;
    }
};

int main() {

}
