#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define vertex int

typedef struct node *link;
typedef struct graph *Graph;

struct node {
  vertex w;
  link next;
};

struct graph {
  int V;
  int E;
  link *adj;
};

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof(struct graph));
  if (!G) { perror("malloc G"); exit(EXIT_FAILURE); }
  G->V = V;
  G->E = 0;
  G->adj = malloc(V * sizeof(link));
  if (!G->adj) { perror("malloc G->adj"); exit(EXIT_FAILURE); }
  for (int i = 0; i < V; i++)
    G->adj[i] = NULL;
  return G;
}

static link NEWnode(vertex w, link next) {
  link a = malloc(sizeof(struct node));
  if (!a) { perror("malloc a"); exit(EXIT_FAILURE); }
  a->w = w;
  a->next = next;
  return a;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
  // verificao se pode adicionar um novo arco
  // for (link a = G->adj[v]; a != NULL; a = a->next)
  //   if (a->w == w) return;
  G->adj[v] = NEWnode(w, G->adj[v]);
  G->E++;
}

static void dfsR(Graph G, int *pre, vertex v, int *cnt) {
  pre[v] = *(cnt++);
  for (link a = G->adj[v]; a != NULL; a = a->next)
    if (pre[a->w] == -1)
      dfsR(G, pre, a->w, cnt);
}

int GRAPHdfs(Graph G) {
  int *pre = malloc(G->V * sizeof(int));
  if (!pre) { perror("malloc pre"); exit(EXIT_FAILURE); }
  for (vertex v = 0; v < G->V; v++)
    pre[v] = -1;

  int cnt = 0;
  int graphs = 0;
  for (vertex v = 0; v < G->V; v++)
    if (pre[v] == -1) {
      graphs++;
      dfsR(G, pre, v, &cnt);
    }
  free(pre);
  return graphs;
}

void GRAPHprint(Graph G) {
  for (vertex v = 0; v < G->V; ++v) {
    printf("%d: ", v);
    for (link a = G->adj[v]; a != NULL; a = a->next)
      (a->next == NULL) ? printf("%d\n", a->w) : printf("%d ", a->w);
  }
}

void GRAPHfree(Graph G) {
  if (G) {
    for (int v = 0; v < G->V; ++v) {
      link curr = G->adj[v];
      while (curr != NULL) {
        link tmp = curr;
        curr = curr->next;
        free(tmp);
      }
    }
    free(G->adj);
    free(G);
  }
}


int main(void) {
  int V;
  scanf("%d", &V);

  Graph G = GRAPHinit(V);

  int v, w;
  // grafo conexo
  while(scanf("%d %d", &v, &w) == 2) {
    GRAPHinsertArc(G, v, w);
    GRAPHinsertArc(G, w, v);
  }

  printf("%d\n", GRAPHdfs(G));

  GRAPHfree(G);

  return 0;
}
