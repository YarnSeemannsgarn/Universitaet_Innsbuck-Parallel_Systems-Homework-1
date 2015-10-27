#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct edge {
  struct node *target_node;
  int distance; 
  struct edge *next; // linked list
} edge_t;

typedef struct node {
  edge_t *edge_head;
  int visited;
  int total_distance;
  struct node *via; // which is the previos node in shorted path
} node_t;

typedef struct unvisited_node{
  node_t *node;
  struct unvisited_node *next; // linked list
} unvisited_node_t;

void add_edge(edge_t **head, node_t *node, int distance);
void free_edges(edge_t *head);
void print_node(node_t *node);
void add_unvisited_node(unvisited_node_t **head, node_t *node);
void remove_unvisited_node(unvisited_node_t **unvisited_nodes, node_t *node);
void free_unvisited_nodes(unvisited_node_t *head);

void dijsktra(node_t *nodes, size_t node_count, node_t *source);
int main(int argc, char *argv[]);

#endif
