
#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct graph {
  int **edges;
  int nV;
  int nE;
};

/*

Common ways the user might implement a graph data structure

=== Adjacency matrix ===
With weighted edges
edges = [
            [0,0,0,1,0],
            [0,0,0,1,0],
            [0,6,0,3,0],
            [0,0,0,0,0],
            [2,0,0,7,8],
        ]

=== Adjacency list ===
Weighted edge shown at the bottom right
edges = [
    0x73428afe -> 0x73428afe -> 0x73428afe -> 0x73428afe -> NULL,
    0x73428afe -> 0x73428afe -> 0x73428afe -> 0x73428afe -> NULL,
    0x73428afe -> 0x73428afe -> 0x73428afe -> 0x73428afe -> NULL,
    0x73428afe -> 0x73428afe -> 0x73428afe -> {edgeData: bool, address,} ->
NULL,
]


The debugger turns the user's graph data structure into a JSON data
representation that can be sent to the visualiser on the frontend.

Possible JSON data representation:

class Node {
    id: int;
    data: int / char / float / etc;
    next: Edge[];
}

class Edge { // do we need this?
    value: int / char / float / etc;   // Acts as an edge weight, but can hold
anything e.g. char
}

graph_nodes: [
            Node(id=0, data=95, next = [Edge(value=1), Edge(value=2)]),
            Node(id=1, data=31, next = [Edge(value=2), Edge(value=3)]),
            Node(id=2, data=42, next = [Edge(value=3)]),
            Node(id=3, data=23, next = [Edge(value=4)]),
            Node(id=4, data=64, next = []),
            Node(id=5, data=14, next = []),
            Node(id=6, data=35, next = [])
       ]

- have option for user to switch between viewing as 2d array OR graph
- consider weighted edges

*/

Graph newGraph(int V) {
  Graph new = malloc(sizeof(struct graph));
  new->nV = V;
  new->nE = 0;

  new->edges = malloc(V * sizeof(int *));
  for (int i = 0; i < V; i++) {
    new->edges[i] = calloc(V, sizeof(int *));
  }
  return new;
}

void addEdge(Graph graph, int v1, int v2) {
  graph->edges[v1][v2] = 1;
  graph->edges[v2][v1] = 1;
}

bool isAdjacent(Graph graph, int v1, int v2) { return graph->edges[v1][v2]; }

void dfsRecursive(Graph graph, int vertex, bool visited[]) {
  visited[vertex] = true;
  printf("Visited vertex %d\n", vertex);

  for (int i = 0; i < graph->nV; i++) {
    if (!visited[i] && isAdjacent(graph, vertex, i)) {
      dfsRecursive(graph, i, visited);
    }
  }
}

void dfs(Graph graph, int vertex) {
  bool *visited = malloc(graph->nV * sizeof(bool));
  dfsRecursive(graph, vertex, visited);
}
