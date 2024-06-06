#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4

typedef struct {
    int puzzle[N][N];
    int x, y; // Blank tile coordinates
    int cost; // Total cost (g + h)
    int level; // g: Number of moves made so far
    struct Node* parent;
} Node;

typedef struct {
    Node** data;
    int size;
    int capacity;
} MinHeap;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Function to print the puzzle
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a given state is the goal state
int isGoal(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != goal[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Function to create a new node
Node* createNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = 0;
    node->x = newX;
    node->y = newY;
    node->cost = INT_MAX;
    node->level = level;
    node->parent = parent;
    return node;
}

// Function to calculate the Manhattan distance heuristic
int calculateCost(int puzzle[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] && puzzle[i][j] != goal[i][j]) {
                int targetX = (puzzle[i][j] - 1) / N;
                int targetY = (puzzle[i][j] - 1) % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Functions for MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->data = (Node**)malloc(sizeof(Node*) * capacity);
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->data[left]->cost < minHeap->data[smallest]->cost)
        smallest = left;

    if (right < minHeap->size && minHeap->data[right]->cost < minHeap->data[smallest]->cost)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->data[smallest], &minHeap->data[idx]);
        minHeapify(minHeap, smallest);
    }
}

Node* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return NULL;

    Node* root = minHeap->data[0];

    if (minHeap->size > 1) {
        minHeap->data[0] = minHeap->data[minHeap->size - 1];
        minHeapify(minHeap, 0);
    }

    minHeap->size--;
    return root;
}

void insertMinHeap(MinHeap* minHeap, Node* node) {
    if (minHeap->size == minHeap->capacity)
        return;

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->data[i] = node;

    while (i && minHeap->data[i]->cost < minHeap->data[(i - 1) / 2]->cost) {
        swap(&minHeap->data[i], &minHeap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to solve the 15-Puzzle problem using the A* algorithm
void solvePuzzle(int puzzle[N][N], int x, int y) {
    MinHeap* openList = createMinHeap(1000);
    Node* root = createNode(puzzle, x, y, x, y, 0, NULL);
    root->cost = calculateCost(puzzle);
    insertMinHeap(openList, root);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (openList->size) {
        Node* minNode = extractMin(openList);

        if (isGoal(minNode->puzzle)) {
            printf("Solved in %d moves.\n", minNode->level);
            Node* temp = minNode;
            while (temp) {
                printPuzzle(temp->puzzle);
                temp = temp->parent;
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = minNode->x + dx[i];
            int newY = minNode->y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = createNode(minNode->puzzle, minNode->x, minNode->y, newX, newY, minNode->level + 1, minNode);
                child->cost = child->level + calculateCost(child->puzzle);
                insertMinHeap(openList, child);
            }
        }

        free(minNode);
    }
}

int main() {
    int puzzle[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int x = 1, y = 2; // Blank tile coordinates
    printf("Initial puzzle:\n");
    printPuzzle(puzzle);

    solvePuzzle(puzzle, x, y);

    return 0;
}
