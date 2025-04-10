#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Job {
    char id;
    int dead;
    int profit;
};

// Bubble Sort to sort jobs by decreasing profit
void bubbleSort(struct Job arr[], int n) {
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].profit < arr[j + 1].profit) {
                // Swap arr[j] and arr[j+1]
                struct Job temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printJobScheduling(struct Job arr[], int n) {
    bubbleSort(arr, n);  // Sort using bubble sort

    int result[n];
    bool slot[n];
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
        slot[i] = false;

    for (int i = 0; i < n; i++) {
        for (int j = arr[i].dead - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = i;
                slot[j] = true;
                totalProfit += arr[i].profit;
                break;
            }
        }
    }

    printf("Job Sequence:\n");
    printf("-----------------------------\n");
    printf("| Job | Deadline | Profit    |\n");
    printf("-----------------------------\n");
    for (int i = 0; i < n; i++) {
        if (slot[i])
            printf("|  %c  |    %d     |   %d     |\n", arr[result[i]].id, arr[result[i]].dead, arr[result[i]].profit);
    }
    printf("-----------------------------\n");
    printf("Total Profit: %d\n", totalProfit);
}

int main() {
    struct Job arr[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15} };

    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Following is the maximum profit sequence of jobs:\n");
    printJobScheduling(arr, n);
    return 0;
}
