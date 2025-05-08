#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int[], int, int);

int main() {
    int list[50];
    int size, i;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    printf("Enter the elements to be sorted:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &list[i]);
    }

    printf("Before applying quick sort\n");
    for (i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    quicksort(list, 0, size - 1);

    printf("\nAfter applying quick sort\n");
    for (i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    printf("\n");
    return 0;  
}

void quicksort(int list[], int low, int high) {
    int pivot, i, j, temp;

    if (low < high) {
        pivot = low;
        i = low + 1; 
        j = high;

        while (i <= j) { 
            while (i <= high && list[i] <= list[pivot]) {
                i++;
            }
            while (j >= low && list[j] > list[pivot]) {
                j--;
            }
            if (i < j) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }

         temp = list[j];
        list[j] = list[pivot];
        list[pivot] = temp;

        quicksort(list, low, j - 1);
        quicksort(list, j + 1, high);
    }
}
