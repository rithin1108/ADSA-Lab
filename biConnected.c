#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int time_counter = 0;
int component_no = 0;

// Structure to represent an edge
typedef struct {
    int u, v;
} Edge;

// Stack for storing edges
typedef struct {
    Edge edges[MAX];
    int top;
} Stack;

// Push an edge onto the stack
void push(Stack *stack, int u, int v) {
    stack->edges[++stack->top] = (Edge){u, v};
}

// Pop an edge from the stack
Edge pop(Stack *stack) {
    return stack->edges[stack->top--];
}

// DFS utility to find Biconnected Components
void findBCCUtil(int u, int disc[], int low[], int parent[], bool visited[],
                 Stack *stack, int adj[MAX][MAX], int V) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time_counter;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                push(stack, u, v);

                findBCCUtil(v, disc, low, parent, visited, stack, adj, V);

                // Update low value
                if (low[v] < low[u])
                    low[u] = low[v];

                // If u is an articulation point, pop edges till (u, v)
                if ((parent[u] == -1 && children > 1) || 
                    (parent[u] != -1 && low[v] >= disc[u])) {
                    component_no++;
                    printf("Biconnected Component %d: ", component_no);
                    while (1) {
                        Edge e = pop(stack);
                        printf("(%d-%d) ", e.u, e.v);
                        if (e.u == u && e.v == v)
                            break;
                    }
                    printf("\n");
                }
            } 
            // Back edge
            else if (v != parent[u] && disc[v] < low[u]) {
                low[u] = disc[v];
                push(stack, u, v);
            }
        }
    }
}

// Main function to find all BCCs
void findBCC(int adj[MAX][MAX], int V) {
    int disc[V], low[V], parent[V];
    bool visited[V];
    Stack stack;
    stack.top = -1;

    // Initialize arrays
    for (int i = 0; i < V; i++) {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
        visited[i] = false;
    }

    // DFS traversal
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            findBCCUtil(i, disc, low, parent, visited, &stack, adj, V);

            // If edges remain in stack, they form a component
            if (stack.top != -1) {
                component_no++;
                printf("Biconnected Component %d: ", component_no);
                while (stack.top != -1) {
                    Edge e = pop(&stack);
                    printf("(%d-%d) ", e.u, e.v);
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    int adj[MAX][MAX] = {0};

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;  // Undirected graph
    }

    printf("\nBiconnected Components:\n");
    findBCC(adj, V);

    return 0;
}
