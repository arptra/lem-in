#include "lem-in.h"

t_adjlistnode	*new_adj_list_node(int dest)
{
	t_adjlistnode	*newNode;
	
	newNode = (t_adjlistnode*) malloc(sizeof(t_adjlistnode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

t_graph	*create_graph(int V)
{
	t_graph*	graph;
	int			i;
	
	graph = (t_graph*) malloc(sizeof(t_graph));
	graph->V = V;
	// Create an array of adjacency lists.  Size of
	// array will be V
	graph->array =(t_adjlist*) malloc(V * sizeof(t_adjlist));
	
	// Initialize each adjacency list as empty by
	// making head as NULL
	i = -1;
	while(++i < V)
		graph->array[i].head = NULL;
	return (graph);
}

// Adds an edge to an undirected graph
void			add_edge(t_graph *graph, int src, int dest)
{
	// Add an edge from src to dest.  A new node is
	// added to the adjacency list of src.  The node
	// is added at the begining
	t_adjlistnode	*newNode;
	
	newNode = new_adj_list_node(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
	
	// Since graph is undirected, add an edge from
	// dest to src also
	newNode = new_adj_list_node(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

void			print_graph(t_graph	*graph)
{
	int v;
	t_adjlistnode	*pCrawl;
	
	v = -1;
	while(++v < graph->V)
	{
		pCrawl = graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}
