//C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph
 
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
 
// Number of vertices in the graph
#define V 6
 
// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int key[], bool spt[])
{
    // Initialize min value
    int v,min = INT_MAX, min_index;
 
    for (v = 0; v < V; v++)
        if (spt[v] == false && key[v] <= min)
            min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed distance
// array
void printSolution(int dist[])
{
    int i;
	printf("Vertex \t\t Distance from Source\n");
    for (i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}
 
// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int key[V],i,count,v; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i
 
    bool spt[V]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
 
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (i = 0; i < V; i++)
        key[i] = INT_MAX, spt[i] = false;
 
    // Distance of source vertex from itself is always 0
    key[src] = 0;
 
    // Find shortest path for all vertices
    for (count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(key, spt);
 
        // Mark the picked vertex as processed
        spt[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!spt[v] && graph[u][v]
                && key[u] != INT_MAX
                && key[u] + graph[u][v] < key[v])
                key[v] = key[u] + graph[u][v];
    }
 
    // print the constructed distance array
    printSolution(key);
}
 
// driver's code
int main()
{
    /* Let us create the example graph discussed above */
    int graph[V][V] = { { 0, 2, 0,0,0,4 },
                        { 2, 0, 8,0,0,3 },
                        { 0,8,0,6,1,0 },
                        { 0,0,6,0,12,0},
                        { 0,0,1,12,0,2 },
						{4,3,0,0,2,0 } };
 
    // Function call
    dijkstra(graph, 0);
 
    return 0;
}
