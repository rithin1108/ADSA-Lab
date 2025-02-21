#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void minHeapify(int arr[],int n,int i)
{
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n&&arr[left]<arr[smallest])
    {
        smallest=left;
    } 

    if(right < n && arr[right]<arr[smallest])
    {
        smallest=right;
    }

    if(smallest!=i)
    {
        swap(&arr[i],&arr[smallest]);
        minHeapify(arr,n,smallest);
    }
}

void buildMinHeap(int arr[],int n)
{
    int i;
    for(i=n/2-1;i>=0;i--)
    {
        minHeapify(arr,n,i);
    }
}

void insertMinHeap(int arr[],int *n,int key)
{
    if(*n>=MAX_SIZE)
    {
        printf("Heap is full\n");
        return;
    }
    (*n)++;
    int i=*n-1;
    arr[i]=key;

     while (i != 0 && arr[(i - 1) / 2] > arr[i]) 
     {
        swap(&arr[i],&arr[(i-1)/2]);
        i=(i-1)/2;
     }
}

void deleteMinHeap(int arr[],int *n)
{
    if(*n<=0)
    return;

    if(*n==1)
    {
        (*n)--;
        return;   
    }

    arr[0]=arr[*n-1];
    (*n)--;
    minHeapify(arr,*n,0);
}

 void displayMinHeap(int arr[],int n)
 {
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d",arr[i]);
    }
    printf("\n");
 }

 void maxHeapify(int arr[], int n, int i) {
 int largest = i;
 int left = 2 * i + 1;
 int right = 2 * i + 2;

 if (left < n && arr[left] > arr[largest]) {
   largest = left;
 }

 if (right < n && arr[right] > arr[largest]) {
  largest = right;
 }

 if (largest != i) {
   swap(&arr[i], &arr[largest]);
   maxHeapify(arr, n, largest);
 }

}

void buildMaxHeap(int arr[], int n) {
 int i;
 for (i = n / 2 - 1; i >= 0; i--) 
 {
 maxHeapify(arr, n, i);

 }

}

void insertMaxHeap(int arr[], int *n, int key) 
{
 if (*n >= MAX_SIZE) 
 {
 printf("Heap is full\n");
 return;

 }

 (*n)++;
 int i = *n - 1;
 arr[i] = key;

 while (i != 0 && arr[(i - 1) / 2] < arr[i]) 
 {
 swap(&arr[i], &arr[(i - 1) / 2]);
 i = (i - 1) / 2;

 }

}

void deleteMaxHeap(int arr[], int *n) 
{
 if (*n <= 0) 
 return;
 if (*n == 1) 
 {
 (*n)--;
 return;

 }

 arr[0] = arr[*n - 1];
 (*n)--;
 maxHeapify(arr, *n, 0);
}


void displayMaxHeap(int arr[], int n) 
{
int i;
 for (i = 0; i < n; i++) 
 {
 printf("%d ", arr[i]);
 }
 printf("\n");
}

int main() {
 int minHeapArr[MAX_SIZE], maxHeapArr[MAX_SIZE];
 int minHeapSize = 0, maxHeapSize = 0;
 int choice, value,i;

 printf("Enter initial number of elements for Min Heap: ");
 scanf("%d", &minHeapSize);
 printf("Enter elements for Min Heap:\n");
 for (i = 0; i < minHeapSize; i++) 
 {
 scanf("%d", &minHeapArr[i]);
 }

 buildMinHeap(minHeapArr, minHeapSize);
 
 printf("Enter initial number of elements for Max Heap: ");
 scanf("%d", &maxHeapSize);
 printf("Enter elements for Max Heap:\n");
 for (i = 0; i < maxHeapSize; i++) 
 {
 scanf("%d", &maxHeapArr[i]);
 }
 buildMaxHeap(maxHeapArr, maxHeapSize);

 while (1) 
 {
  printf("\n1. Insert into Min Heap\n");
  printf("2. Delete from Min Heap\n");
  printf("3. Display Min Heap\n");
  printf("4. Insert into Max Heap\n");
  printf("5. Delete from Max Heap\n");
  printf("6. Display Max Heap\n");
  printf("7. Exit\n");
  printf("Enter your choice: ");
  scanf("%d", &choice);


 switch (choice) {
   case 1:

    printf("Enter value to insert into Min Heap: ");
    scanf("%d", &value);
    insertMinHeap(minHeapArr, &minHeapSize, value);
    printf("Min Heap after insertion: ");
    displayMinHeap(minHeapArr, minHeapSize);
    break;

 case 2:

   deleteMinHeap(minHeapArr, &minHeapSize);
   printf("Min Heap after deletion: ");
   displayMinHeap(minHeapArr, minHeapSize);
   break;

 case 3:

   printf("Min Heap: ");
   displayMinHeap(minHeapArr, minHeapSize);
   break;

 case 4:

   printf("Enter value to insert into Max Heap: ");
   scanf("%d", &value);
   insertMaxHeap(maxHeapArr, &maxHeapSize, value);
   printf("Max Heap after insertion: ");
   displayMaxHeap(maxHeapArr, maxHeapSize);
   break;

 case 5:

   deleteMaxHeap(maxHeapArr, &maxHeapSize);
   printf("Max Heap after deletion: ");
   displayMaxHeap(maxHeapArr, maxHeapSize);
   break;

 case 6:

   printf("Max Heap: ");
   displayMaxHeap(maxHeapArr, maxHeapSize);
   break;

 case 7:

   exit(0);
   default:
   printf("Invalid choice!\n");
 }

 }
 return 0;
}
