#include <stdio.h>
#include <limits.h>

#define V 4
#define INF INT_MAX

int tspDP(int cost[][V], int n) {
    int memo[n][1 << n];
    
    // Initialize memo table with INF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            memo[i][j] = INF;
        }
    }

    // Base case: start from the first city
    for (int i = 0; i < n; i++) {
        memo[i][1 << i] = cost[0][i];
    }

    // Fill the memo table
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < n; j++) {
                    if (i != j && (mask & (1 << j))) {
                        memo[i][mask] = memo[i][mask] < memo[j][mask ^ (1 << i)] + cost[j][i] ? memo[i][mask] : memo[j][mask ^ (1 << i)] + cost[j][i];
                    }
                }
            }
        }
    }

    // Find the minimum cost to return to the starting point
    int minCost = INF;
    for (int i = 1; i < n; i++) {
        minCost = minCost < memo[i][(1 << n) - 1] + cost[i][0] ? minCost : memo[i][(1 << n) - 1] + cost[i][0];
    }

    return minCost;
}

int main() {
    int cost[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    printf("Minimum cost using Dynamic Programming: %d\n", tspDP(cost, V));
    return 0;
}
