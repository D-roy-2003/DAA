#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX], front = -1, rear = -1;
int visited[MAX] = {0};

void enqueue(int vertex) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = vertex;
}

int dequeue() {
    if (front == -1)
        return -1;
    int vertex = queue[front++];
    if (front > rear)
        front = rear = -1;
    return vertex;
}

void BFS(int graph[MAX][MAX], int start, int n) {
    enqueue(start);
    visited[start] = 1;
    while (front != -1) {
        int current = dequeue();
        printf("%d ", current);
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n = 6;
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0}
    };
    printf("BFS starting from vertex 0:\n");
    BFS(graph, 0, n);
    return 0;
}
