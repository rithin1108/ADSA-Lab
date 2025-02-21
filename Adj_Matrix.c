
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX) {
        printf("Queue is full\n");
        return;
    }
    q->items[q->rear++] = value;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front++];
}

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack is full\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top--];
}

void bft_adjacency_matrix(int matrix[MAX][MAX], int start, int n) {
    int i;
    int visited[MAX] = {0};
    Queue* q = createQueue();
    visited[start] = 1;
    enqueue(q, start);

    printf("BFT using Adjacency Matrix: ");
    
    while (!isQueueEmpty(q)) {
        int node = dequeue(q);
        printf("%d ", node);

        for (i = 0; i < n; i++) {
            if (matrix[node][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
}

void dft_adjacency_matrix(int matrix[MAX][MAX], int start, int n) {
    int i;
    int visited[MAX] = {0};
    Stack* s = createStack();
    push(s, start);
    
    printf("DFT using Adjacency Matrix: ");
    
    while (!isStackEmpty(s)) {
        int node = pop(s);
        
        if (!visited[node]) {
            printf("%d ", node);
            visited[node] = 1;
            
            for (i = n - 1; i >= 0; i--) {
                if (matrix[node][i] == 1 && !visited[i]) {
                    push(s, i);
                }
            }
        }
    }
    printf("\n");
}

int main() {
    int matrix[MAX][MAX] = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };
    
    int n = 4;
    
    bft_adjacency_matrix(matrix, 0, n);
    dft_adjacency_matrix(matrix, 0, n);

    return 0;    
    
}
