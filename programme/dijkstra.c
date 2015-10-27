#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"
#include "common.h"

// ==================================================================================
// Helper
// ==================================================================================
void add_edge(edge_t **head, node_t *node, int distance) {
  edge_t *current = *head;
  // no head exists
  if((*head) == NULL){
    (*head) = malloc(sizeof(edge_t));
    (*head)->target_node = node;
    (*head)->distance = distance;
    (*head)->next = NULL;
  }
  else{
    while (current->next != NULL) {
      current = current->next;
    }
  
    current->next = malloc(sizeof(edge_t));
    current->next->target_node = node;
    current->next->distance = distance;
    current->next->next = NULL;
  }
}

void free_edges(edge_t *head){
  edge_t *current;
  while((current = head) != NULL) {
    head = head->next;      
    free (current);          
  }
}


void print_node(node_t *node){
  printf("Node: %p\n", node);
  edge_t *current_edge = node->edge_head;
  while(current_edge != NULL) {
    printf("Edge to node: %p with distance %i\n", current_edge->target_node, current_edge->distance);
    current_edge = current_edge->next;
  }
  printf("Shortest path Via: %p\n", node->via);
  printf("Total distance: %i\n", node->total_distance);
  printf("\n");
}

void add_unvisited_node(unvisited_node_t **head, node_t *node) {
  // no head exists
  unvisited_node_t *current = *head;
  if((*head) == NULL){
    (*head) = malloc(sizeof(unvisited_node_t));
    (*head)->node = node;
    (*head)->next = NULL;
  }
  else{
    while (current->next != NULL) {
      current = current->next;
    }
  
    current->next = malloc(sizeof(unvisited_node_t));
    current->next->node = node;
    current->next->next = NULL;
  }
}

void remove_unvisited_node(unvisited_node_t **unvisited_nodes, node_t *node)
{
  unvisited_node_t *current, *previous;

  /* For 1st node, indicate there is no previous. */
  previous = NULL;

  /*
   * Visit each node, maintaining a pointer to
   * the previous node we just visited.
   */
  for (current = *unvisited_nodes;
	current != NULL;
	previous = current, current = current->next) {

    if (current->node == node) {  /* Found it. */
      if (previous == NULL) {
        /* Fix beginning pointer. */
        *unvisited_nodes = current->next;
      } else {
        /*
         * Fix previous node's next to
         * skip over the removed node.
         */
        previous->next = current->next;
      }

      /* Deallocate the node. */
      free(current);

      /* Done searching. */
      return;
    }
  }
}

void free_unvisited_nodes(unvisited_node_t *head){
  unvisited_node_t *current;
  while((current = head) != NULL) {
    head = head->next;      
    free (current);            
  }
}

// ==================================================================================
// Algorithm taken from: https://en.wikipedia.org/wiki/Dijkstra's_algorithm#Algorithm
// ==================================================================================
void dijsktra(node_t *nodes, size_t node_count, node_t *source){
  // --------------------------------------------------------------------------------
  // 1. Assign to every node a tentative distance value: 
  // set it to zero for our initial node and to infinity for all other nodes.
  // 2. Set the initial node as current. Mark all other nodes unvisited. 
  // Create a set of all the unvisited nodes called the unvisited set.
  // --------------------------------------------------------------------------------
  int i;
  node_t *current = source;
  current->visited = 1;
  current->via = source;
  unvisited_node_t *unvisited_nodes_head = NULL;
  for(i=0; i<node_count; ++i){
    if(&nodes[i] != source){
      nodes[i].total_distance = -1; //equal infinity
      add_unvisited_node(&unvisited_nodes_head, &nodes[i]);
    }
  }

  // --------------------------------------------------------------------------------
  // 3. For the current node, consider all of its unvisited neighbors and 
  // calculate their tentative distances. Compare the newly calculated 
  // tentative distance to the current assigned value and assign the smaller one. 
  // For example, if the current node A is marked with a distance of 6, and the 
  // edge connecting it with a neighbor B has length 2, then the distance to B (through A) 
  // will be 6 + 2 = 8. If B was previously marked with a distance greater than 8 
  // then change it to 8. Otherwise, keep the current value.
  // --------------------------------------------------------------------------------
  while(1){
    edge_t *edge = current->edge_head;
    node_t *target_node;
    int new_calculated;
    while(edge != NULL){
      target_node = edge->target_node;
      if(target_node->visited == 0){
	new_calculated = current->total_distance + edge->distance;
	if(target_node->total_distance == -1 || 
	   target_node->total_distance > new_calculated){
	  target_node->total_distance = new_calculated;
	  target_node->via = current;
	}
      }
      edge = edge->next;
    }

    // --------------------------------------------------------------------------------
    // 4. When we are done considering all of the neighbors of the current node, 
    // mark the current node as visited and remove it from the unvisited set. 
    // A visited node will never be checked again.
    // --------------------------------------------------------------------------------
    current->visited = 1;
    remove_unvisited_node(&unvisited_nodes_head, current);

    // --------------------------------------------------------------------------------
    // 5. [...] if the smallest tentative distance among the #nodes in the unvisited 
    // set is infinity (when planning a complete traversal; occurs when there is no 
    // connection between the initial node and remaining unvisited nodes), 
    // then stop. The algorithm has finished.
    // 6. Otherwise, select the unvisited node that is marked with the smallest tentative 
    // distance, set it as the new "current node", and go back to step 3
    // --------------------------------------------------------------------------------
    unvisited_node_t *next_unvisited_node = unvisited_nodes_head;
    node_t *next_current = NULL;
    while(next_unvisited_node != NULL){
      if(next_unvisited_node->node->total_distance != -1){
	if(next_current == NULL || 
	   next_current->total_distance > next_unvisited_node->node->total_distance){
	  next_current = next_unvisited_node->node;
	}
      }
      next_unvisited_node = next_unvisited_node->next;
    }
    if(next_current == NULL){
      free_unvisited_nodes(unvisited_nodes_head);
      return;
    }
    else{
      current = next_current;
    }
  }
}

// ==================================================================================
// main
// ==================================================================================
int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create N nodes
  node_t *nodes = calloc(N, sizeof(node_t));
  int i, j, distance;
  int edge_count = 0;
  srand48(time(NULL));
  for(i=0; i<(N-1); ++i){
    for(j=i+1; j<N; ++j){
      // Add edges
      distance = lrand48() % RANGE_MAX + 1;
      add_edge(&(nodes[i].edge_head), &nodes[j], distance);
      add_edge(&(nodes[j].edge_head), &nodes[i], distance);
      edge_count++;
    }
  }
  
  //Print nodes with edges
  //for(i=0; i<N; ++i){
  //print_node(&nodes[i]);
  //}

  // Measure time
  clock_t begin, end;
  double time_spent;
  printf("Starting dijkstra for problem size (node) %zu and %i edges\n", N, edge_count);
  begin = clock();
  dijsktra(nodes, N, &nodes[0]);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  // Free memory
  for(i=0; i<N; ++i){
    //print_node(&nodes[i]);
    free_edges(nodes[i].edge_head);
  }  
  free(&nodes[0]);

  return EXIT_SUCCESS;
}
