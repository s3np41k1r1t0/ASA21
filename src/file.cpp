#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
 private:
  class Edge {
   private:
    unsigned int *actual;
    unsigned int *capacity;
    unsigned int dest;

   public:
    Edge(unsigned int *cap, unsigned int *actual, unsigned int dest) {
      this->actual = actual;
      this->capacity = cap;
      this->dest = dest;
    }

    friend class Graph;
    friend class Vertex;
  };

  class Vertex {
   private:
    friend class Edge;
    vector<Edge *> adj;
    unsigned int flow = 0;
    unsigned int heigth = 0;
    unsigned int id, start;
    int rank;

    friend class Graph;
  };

  Vertex *graph;
  unsigned int size;
  unsigned int result = 0;
  void discharge(Vertex *u);
  bool bfs();
  int dfs(Vertex *v, int flow);

 public:
  Graph(unsigned int n);
  void insert(unsigned int &x, unsigned int &y, unsigned int &cap);
  void insertX(unsigned int &v, unsigned int &cap);
  void insertY(unsigned int &v, unsigned int &cap);
  void solve();
};

// O(V)
Graph::Graph(unsigned int n) {
  size = n;
  graph = new Vertex[n];

  for (unsigned int i = 0; i < n; i++) {
    graph[i].id = i;
  }
}

// O(1)
void Graph::insert(unsigned int &x, unsigned int &y, unsigned int &cap) {
  unsigned int cap_copy = static_cast<unsigned int>(cap);
  unsigned int actual = static_cast<unsigned int>(0);
  graph[x + 1].adj.push_back(new Edge(&cap_copy, &actual, y + 1));
  graph[y + 1].adj.push_back(new Edge(&cap_copy, &actual, x + 1));
}

// O(1)
void Graph::insertX(unsigned int &v, unsigned int &cap) {
  unsigned int cap_copy = static_cast<unsigned int>(cap);
  unsigned int actual = static_cast<unsigned int>(0);
  graph[0].adj.push_back(new Edge(&cap_copy, &actual, v + 1));
}

// O(1)
void Graph::insertY(unsigned int &v, unsigned int &cap) {
  unsigned int cap_copy = static_cast<unsigned int>(cap);
  unsigned int actual = static_cast<unsigned int>(0);
  graph[1].adj.push_back(new Edge(&cap_copy, &actual, v + 1));
}

bool Graph::bfs() {
  for (unsigned int i = 0; i < size; i++) {
    graph[i].rank = -1;
  }

  queue<Vertex *> q;
  q.push(&graph[0]);
  graph[0].rank = 0;

  while (!q.empty()) {
    Vertex *v = q.front();

    for (vector<Edge *>::iterator it = v->adj.begin(); it != v->adj.end();
         ++it) {
      Edge *e = *it;

      if (graph[e->dest].rank < 0 && *(e->actual) < *(e->capacity)) {
        graph[e->dest].rank += 1;
        q.push(&graph[e->dest]);
      }
    }
  }

  return graph[1].rank >= 0;
}

int Graph::dfs(Vertex *v, int flow) {
  if (v->id == 1) {
    return flow;
  }

  for (; v->start < v->adj.size(); v->start++) {
    Edge *e = v->adj[v->start];

    if (*(e->capacity) <= *(e->actual)) {
      continue;
    }

    if (v->heigth == graph[e->dest].heigth + 1) {
      flow =
          dfs(&graph[e->dest], min(flow, (int)(*(e->capacity) - *(e->actual))));

      if (flow != 0) {
        *(e->actual) += flow;
        return flow;
      }
    }
  }

  return 0;
}

void Graph::solve() {
  while (bfs()) {
    for (unsigned int i = 0; i < size; i++) {
      graph[i].start = 0;
    }

    while (int flow = dfs(&graph[0], INT_MAX)) {
      result += flow;
    }
  }

  cout << result << endl;
}

int main() {
  unsigned int x, y, n, m;

  if (scanf("%d %d\n", &n, &m) == -1) return 1;

  Graph g(n + 2);

  for (unsigned int i = 1; i <= n; i++) {
    if (scanf("%d %d\n", &x, &y) == -1) return 1;
    g.insertY(i, y);
    g.insertX(i, x);
  }

  while (m > 0) {
    if (scanf("%d %d %d\n", &x, &y, &n) == -1) return 1;
    g.insert(x, y, n);
    m--;
  }

  g.solve();

  return 0;
}
