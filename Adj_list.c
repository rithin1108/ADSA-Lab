#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Structure for an adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for the graph
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
    int visited[MAX];
} Graph;

// Queue structure for BFT
typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

// Stack structure for DFT
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Function to create a new node in the adjacency list
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int vertices) {
    int i;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph (for undirected graph)
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (since the graph is undirected)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to create a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    return q;
}

// Check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// Enqueue an element
void enqueue(Queue* q, int value) {
    if (q->rear == MAX) {
        printf("Queue is full\n");
        return;
    }
    q->items[q->rear++] = value;
}

// Dequeue an element
int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front++];
}

// Function to create a stack
Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

// Check if the stack is empty
int isStackEmpty(Stack* s) {
    return s->top == -1;
}

// Push an element onto the stack
void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack is full\n");
        return;
    }
    s->items[++s->top] = value;
}

// Pop an element from the stack
int pop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top--];
}

// Function to perform Breadth-First Traversal using adjacency list
void bft_adjacency_list(Graph* graph, int start) {
    Queue* q = createQueue();
    graph->visited[start] = 1;
    enqueue(q, start);
    printf("BFT using Adjacency List: ");
    
    while (!isQueueEmpty(q)) {
        int node = dequeue(q);
        printf("%d ", node);

        // Visit all the neighbors of the current vertex
        Node* temp = graph->adjLists[node];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Function to perform Depth-First Traversal using adjacency list
void dft_adjacency_list(Graph* graph, int start) {
    Stack* s = createStack();
    push(s, start);
    printf("DFT using Adjacency List: ");
    
    while (!isStackEmpty(s)) {
        int node = pop(s);
        if (!graph->visited[node]) {
            printf("%d ", node);
            graph->visited[node] = 1;

            // Push all the neighbors of the current vertex
            Node* temp = graph->adjLists[node];
            while (temp) {
                int adjVertex = temp->vertex;
                if (!graph->visited[adjVertex]) {
                    push(s, adjVertex);
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

int main() {
    int i;
    
    // Create a graph with 4 vertices
    Graph* graph = createGraph(4);
    
    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    
    // Perform BFT and DFT starting from vertex 0
    bft_adjacency_list(graph, 0);

    // Reset visited array for DFT
    for (i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    dft_adjacency_list(graph, 0);

    return 0;
}
