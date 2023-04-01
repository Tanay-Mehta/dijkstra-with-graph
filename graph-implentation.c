#include <stdio.h>
#include <stdlib.h>

struct node{
    int vertex;
    int weight;
    struct node* next;
};

struct graph{
    int numVertices;
    struct node** adjLists;
};

struct node* create_node(int s, int w){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->weight = w;
    newNode->vertex = s;
    newNode->next = NULL;
    return newNode;
};

struct graph* createAGraph(int No_of_vertices){
    struct graph* NewGraph = (struct graph*)malloc(sizeof(struct graph));
    NewGraph->numVertices = No_of_vertices;
    NewGraph->adjLists = malloc(No_of_vertices* sizeof(struct node));
    int i;
    for(i=0;i<No_of_vertices;i++){
        NewGraph->adjLists[i] = NULL;
    }
    return NewGraph;
}

void AddEdge(struct graph* G1, int src, int dest, int weight){
    struct node* newNode = create_node(dest, weight);
    newNode->next = G1->adjLists[src];
    G1->adjLists[src] = newNode;
    newNode = create_node(src, weight);
    newNode->next = G1->adjLists[dest];
    G1->adjLists[dest] = newNode;
}

void printGraph(struct graph* Graph) {
  int v;
  for (v = 0; v < Graph->numVertices; v++) {
    struct node* temp = Graph->adjLists[v];
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}
int* djkstra(struct graph* Graph, int array[]){
  int unvisited_nodes[Graph->numVertices];
  for(int i=0;i<Graph->numVertices;i++){
    unvisited_nodes[i] = i;
  }
  for(int i=0;i<Graph->numVertices;i++){
    array[i] = 99;
  }
  array[0] = 0;
  for(int src=0; src<Graph->numVertices; src++){
    struct node* temp = Graph->adjLists[src];
    while (temp) {
        if(temp->weight < array[temp->vertex]){
          if(array[temp->vertex] == 99){
            array[temp->vertex] = temp->weight;
          }
          if(temp->weight+array[src] < array[temp->vertex]){
            array[temp->vertex] = temp->weight+array[src];
          }
        }
        temp = temp->next;
      }
  }
  return array;
}

int main() {
  struct graph* Graph = createAGraph(4);
  AddEdge(Graph, 0, 1, 2);
  AddEdge(Graph, 0, 2, 4);
  AddEdge(Graph, 1, 3, 5);
  AddEdge(Graph, 3, 2, 3);
  AddEdge(Graph, 1, 2, 1);
  AddEdge(Graph, 0, 3, 3);
  int array[Graph->numVertices];
  djkstra(Graph, array);
  for(int i=0;i<Graph->numVertices;i++){
    printf("%i", array[i]);
  }
  printGraph(Graph);

  return 0;
}
