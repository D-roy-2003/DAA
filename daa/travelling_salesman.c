// Implementation of TSP will be quite lengthy due to its complexity. 
// Here's a simplified version using brute-force for small instances.
// Travelling Salesman
#include <stdio.h>
#include <limits.h>

#define V 4 // Number of vertices

int graph[V][V] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

int tsp(int visited, int pos) {
    if (visited == (1 << V) - 1)
        return graph[pos][0];

    int min_cost = INT_MAX;

    for (int i = 0; i < V; i++) {
        if (!(visited & (1 << i))) {
            int cost = graph[pos][i] + tsp(visited | (1 << i), i);
            min_cost = min(min_cost, cost);
        }
    }
    return min_cost;
}

int main() {
    printf("Minimum cost: %d\n", tsp(1, 0)); // Output: Minimum cost: 80
    return 0;
}
