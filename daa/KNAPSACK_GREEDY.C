#include <stdio.h>
#include <stdlib.h>

// A structure to represent an item
typedef struct {
    int value;
    int weight;
} Item;

// Function to compare two items based on value/weight ratio
int compare(const void *a, const void *b) {
    double r1 = (double)((Item *)a)->value / ((Item *)a)->weight;
    double r2 = (double)((Item *)b)->value / ((Item *)b)->weight;
    return r2 > r1 ? 1 : -1;
}

// Function to calculate the maximum value we can get
double fractionalKnapsack(int W, Item arr[], int n) {
    qsort(arr, n, sizeof(Item), compare);
    
    int curWeight = 0;  // Current weight in knapsack
    double finalValue = 0.0;  // Result (value in knapsack)
    
    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            finalValue += arr[i].value;
        } else {
            int remain = W - curWeight;
            finalValue += arr[i].value * ((double) remain / arr[i].weight);
            break;
        }
    }
    
    return finalValue;
}

int main() {
    int W = 50;  // Weight of knapsack
    Item arr[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Maximum value we can obtain = %f\n", fractionalKnapsack(W, arr, n));
    return 0;
}
