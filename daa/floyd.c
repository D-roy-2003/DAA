//Floyd

#include <stdio.h>
#include <limits.h>

#define V 5  // Number of vertices in the graph
#define INF INT_MAX  // Representation of infinity

// Function to print the solution matrix
void printSolution(int dist[][V]) {
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement the Floyd-Warshall algorithm
void floydWarshall(int graph[][V]) {
    int dist[V][V], i, j, k;

    // Initialize the solution matrix same as input graph matrix
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Add all vertices one by one to the set of intermediate vertices
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    // Print the shortest distance matrix
    printSolution(dist);
}

int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 5, 2, 10, 6},
        {5, 0, 13, 4, INF},
        {2, 13, 0, 9, 3},
        {10, 4, 9, 0, 4},
        {6, INF, 3, 4, 0}
    };

    // Run the Floyd-Warshall algorithm
    floydWarshall(graph);
    return 0;

}