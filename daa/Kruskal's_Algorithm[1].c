#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Function prototypes
int find(int parent[], int i);
void Union(int parent[], int rank[], int x, int y);
void kruskalMST(int V, int graph[][V]);

int main() {
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    int graph[V][V];
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }
    kruskalMST(V, graph);
    return 0;
}
// Function to find set of an element i
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}
// Function to perform union of two sets x and y
void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        ++rank[xroot];
    }
}
// Function to perform Kruskal's algorithm
void kruskalMST(int V, int graph[V][V]) {
    // Initialize variables
    int parent[V];
    int rank[V];
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
    printf("Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (int count = 0; count < V - 1; ++count) {
        int minWeight = INT_MAX;
        int u, v;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (graph[i][j] && find(parent, i) != find(parent, j) && graph[i][j] < minWeight) {
                    minWeight = graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        printf("%d - %d Weight: %d\n", u, v, minWeight);
        totalWeight += minWeight;
        Union(parent, rank, u, v);
    }

    printf("Total weight of MST: %d\n", totalWeight);
}
