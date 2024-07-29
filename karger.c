#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Edge {
    int src, dest;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edges;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*) malloc(E * sizeof(Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int kargerMinCut(Graph* graph) {
    int V = graph->V;
    int E = graph->E;
    Edge* edges = graph->edges;

    int* parent = (int*) malloc(V * sizeof(int));
    int* rank = (int*) malloc(V * sizeof(int));

    for (int v = 0; v < V; ++v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int vertices = V;

    while (vertices > 2) {
        int i = rand() % E;

        int subset1 = find(parent, edges[i].src);
        int subset2 = find(parent, edges[i].dest);

        if (subset1 == subset2)
            continue;
        else {
            Union(parent, rank, subset1, subset2);
            vertices--;
        }
    }

    int cutEdges = 0;
    for (int i = 0; i < E; i++) {
        int subset1 = find(parent, edges[i].src);
        int subset2 = find(parent, edges[i].dest);
        if (subset1 != subset2)
            cutEdges++;
    }

    return cutEdges;
}

int main() {

    srand(time(NULL));

    int V = 4;
    int E = 5;
    Graph* graph = createGraph(V, E);
	
    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[2].src = 0;
    graph->edges[2].dest = 3;
    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[4].src = 2;
    graph->edges[4].dest = 3;

    int matrix[4][4];
     for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
		matrix[i][j] = 0; 
	}
 }   
    for (int i = 0; i < 5; i++) {
	matrix[graph->edges[i].src][graph->edges[i].dest] = 1;
	matrix[graph->edges[i].dest][graph->edges[i].src] = 1;
    }

    for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
		printf("%d ", matrix[i][j]); 
	}
	printf("\n");
    }

    int minCut = E;
    for (int i = 0; i < 1; i++) {
        int cut = kargerMinCut(graph);
        if (cut < minCut)
            minCut = cut;
    }

	int bmincut = E;
	int counter = 0;
    	for (int i = 0; i < (1 << V); i++) {
		if (i == 0 || i == (1 << V) - 1)
			continue;
		for (int j = 0; j < E; j++) {
			graph->edges[j];
			if (((i>>graph->edges[j].src) & 1 ) ^ ((i>>graph->edges[j].dest) & 1)) {
				counter++;	
			}
		}
		bmincut = bmincut > counter ? counter : bmincut;
		counter = 0;
	}

	printf("Brute force min cut: %d\n\n", bmincut);

    printf("Minimum cut found by Karger's Algorithm is %d\n", minCut);

    return 0;
}

