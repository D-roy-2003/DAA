#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define V 4

int findMinCost(int cost[][V], int visited[], int currentPos) {
    int minCost = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && cost[currentPos][i] < minCost) {
            minCost = cost[currentPos][i];
            minIndex = i;
        }
    }
    return minIndex;
}

int tspGreedy(int cost[][V]) {
    int visited[V] = {0};
    int minCost = 0;
    int currentPos = 0;
    visited[currentPos] = 1;
    for (int i = 1; i < V; i++) {
        int nextPos = findMinCost(cost, visited, currentPos);
        visited[nextPos] = 1;
        minCost += cost[currentPos][nextPos];
        currentPos = nextPos;
    }
    minCost += cost[currentPos][0]; // Returning to the starting point
    return minCost;
}

int main() {
    int cost[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    printf("Minimum cost using Greedy: %d\n", tspGreedy(cost));
    return 0;
}
