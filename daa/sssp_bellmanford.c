#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999

struct Edge
{
  int source, dest, weight;
};

void printDistance(int distance[], int v)
{
  printf("Vertex\tDistance from Source\n");
  for(int i = 0; i < v; i++) {
    if(distance[i] == INF)
      printf("%d\t%s\n", i, "INF");
    else
      printf("%d\t%d\n", i, distance[i]);
  }
}

void bellman(struct Edge edges[], int v, int e, int source, int distance[])
{
  for(int i = 0; i < v; i++) {
    distance[i] = INF;
  }
  distance[source] = 0;
  for(int i = 0; i < v-1; i++) {
    for(int j = 0; j < e; j++) {
      int u = edges[j].source;
      int v = edges[j].dest;
      int w = edges[j].weight;
      if(distance[u] != INF && distance[u] + w < distance[v])
        distance[v] = distance[u] + w;
    }
  }
  for(int i = 0; i < e; i++) {
    int u = edges[i].source;
    int v = edges[i].dest;
    int w = edges[i].weight;
    if(distance[u] != INF && distance[u] + w < distance[v]) {
      printf("Graph contains negative weight cycle\n");
      return;
    }
  }  
}

int main()
{
  int v = 4;
  int e = 4;
  // struct Edge edges[] = {{0, 1, 6}, {0, 2, 5}, {0, 3, 5}, {1, 4, -1}, {2, 1, -2},
  //                       {2, 4, 1}, {3, 2, -2}, {3, 5, -1}, {4, 6, 3}, {5, 6, 3}};
  struct Edge edges[] = {{0, 3, 5}, {0, 1, 4}, {2, 1, -10}, {3, 2, 3}};
  int distance[v];
  int source = 0;
  bellman(edges, v, e, source, distance);
  printDistance(distance, v);

 return 0;
}