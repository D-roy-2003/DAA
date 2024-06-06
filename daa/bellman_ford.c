//Bellman_Ford

// Implementation of Bellman-Ford Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5 // Number of vertices
#define E 8 // Number of edges

typedef struct {
    int src, dest, weight;
} Edge;

Edge edges[E];
int dist[V];

void bellmanFord(int src) {
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

int main() {
    edges[0].src = 0; edges[0].dest = 1; edges[0].weight = -1;
    edges[1].src = 0; edges[1].dest = 2; edges[1].weight = 4;
    edges[2].src = 1; edges[2].dest = 2; edges[2].weight = 3;
    edges[3].src = 1; edges[3].dest = 3; edges[3].weight = 2;
    edges[4].src = 1; edges[4].dest = 4; edges[4].weight = 2;
    edges[5].src = 3; edges[5].dest = 2; edges[5].weight = 5;
    edges[6].src = 3; edges[6].dest = 1; edges[6].weight = 1;
    edges[7].src = 4; edges[7].dest = 3; edges[7].weight = -3;

    bellmanFord(0);

    return 0;
}
