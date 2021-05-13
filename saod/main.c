#include "graph.h"
#include "heap.h"
#include <limits.h>
#include <time.h>


void dijkstra(struct graph *g, int s, int *D, int *prev) 
{
	struct heap *q = heap_create(g->nvertices);
	struct heapnode minnode;

	for (int i = 1; i <= g->nvertices; i++)
    {
        if(i == s) 
        	D[i] = 0;
        else
        	D[i] = INT_MAX;

        prev[i] = -1;
        heap_insert(q, D[i], i);
    }

	for (int i = 0; i < g->nvertices ; i++) {
		minnode = heap_extract_min(q);
		g->visited[minnode.value - 1] = 1;

		for (int j = 1; j <= g->nvertices; j++) {	
			if (graph_get_edge(g, minnode.value, j)  && !g->visited[j-1]){
				if(graph_get_edge(g, minnode.value, j) + D[minnode.value] < D[j]) {
					D[j] = graph_get_edge(g, minnode.value, j) + D[minnode.value];
					heap_decrease_key(q, j, D[j]);
					prev[j] = minnode.value;
					
				}
			}
		}
	}
	heap_free(q);
}

void graph_init(struct graph *g)\
{
	for(int i = 1; i < g->nvertices; i++)
		graph_set_edge(g, i, i+1, i);
}

void grid_init(struct graph *g)
{
	for(int i = 1; i < g->nvertices; i++) {
		if((i % 100 == 0) && (i < 9900)) {
			graph_set_edge(g, i, i+100, 1);
		}
		else if((i < 9900) && (i % 100 != 0)) { 
			graph_set_edge(g, i, i+1, 1);
			graph_set_edge(g, i, i+100, 1);
		}
		else
			graph_set_edge(g, i, i+1, 1);
	}
}

int main()
{
	struct graph *z = graph_create(20);
	int *prev = malloc(sizeof(int) * (z->nvertices + 1));
	int *D = malloc(sizeof(int) * (z->nvertices + 1));
	//grid_init(z);
	graph_init(z);

	/*graph_set_edge(z, 1, 2, 10);
	graph_set_edge(z, 1, 5, 20);
	graph_set_edge(z, 2, 3, 20);
	graph_set_edge(z, 2, 4, 40);
	graph_set_edge(z, 3, 7, 10);
	graph_set_edge(z, 4, 15, 10);
	graph_set_edge(z, 5, 11, 10);
	graph_set_edge(z, 5, 6, 60);
	graph_set_edge(z, 6, 10, 20);
	graph_set_edge(z, 7, 8, 30);
	graph_set_edge(z, 7, 9, 10);
	graph_set_edge(z, 8, 16, 40);
	graph_set_edge(z, 8, 17, 20);
	graph_set_edge(z, 10, 12, 10);
	graph_set_edge(z, 12, 13, 5);
	graph_set_edge(z, 13, 14, 5);
	graph_set_edge(z, 13, 15, 10);
	graph_set_edge(z, 14, 20, 10);
	graph_set_edge(z, 15, 16, 20);
	graph_set_edge(z, 15, 18, 40);
	graph_set_edge(z, 17, 19, 20);
	graph_set_edge(z, 18, 19, 40);
	graph_set_edge(z, 19, 20, 60);
	graph_set_edge(z, 4, 14, 20);*/

	clock_t Time = clock();
	dijkstra(z, 1, D, prev);
	clock_t Time2 = clock();
	double Timeend = (double)(Time2 - Time)/ CLOCKS_PER_SEC;
	printf("%f\n\n", Timeend);
	for (int i = 1; i < z->nvertices + 1; i++)
		printf("%d ", D[i]);
	printf("\n");
}
