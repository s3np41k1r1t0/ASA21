#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

#define MAX_INT 2147483647

using namespace std;

class Graph {
 private:
  class Vertex {
   private:
    int id;
    map<int, int> capacity;
    vector<Vertex *> adj;
    Vertex *parent = nullptr;

    friend class Graph;
  };

  Vertex *graph;
  int size;
  int result = 0;
  int bfs();

 public:
  Graph(int n);
  void insert(int &x, int &y, int cap);
  void insertX(int &v, int cap);
  void insertY(int &v, int cap);
  void solve();
};

// O(V)
Graph::Graph(int n) {
  size = n;
  graph = new Vertex[n];

  for (int i = 0; i < n; i++) {
    graph[i].id = i;
  }
}

void Graph::insert(int &x, int &y, int cap) {
  graph[x + 1].adj.push_back(&graph[y + 1]);
  graph[y + 1].adj.push_back(&graph[x + 1]);
  graph[x + 1].capacity[y + 1] = cap;
  graph[y + 1].capacity[x + 1] = cap;
}

void Graph::insertX(int &v, int cap) {
  graph[0].adj.push_back(&graph[v + 1]);
  graph[0].capacity[v + 1] = cap;
  graph[v + 1].capacity[0] = 0;
}

void Graph::insertY(int &v, int cap) {
  graph[v + 1].adj.push_back(&graph[1]);
  graph[v + 1].capacity[1] = cap;
  graph[1].capacity[v + 1] = 0;
}

int Graph::bfs() {
  int previous_flow, result_flow;

  for (int i = 0; i < size; i++) {
    graph[i].parent = nullptr;
  }

  queue<pair<Vertex *, int> > q;
  q.push(make_pair(&graph[0], MAX_INT));

  while (!q.empty()) {
    Vertex *v = q.front().first;
    previous_flow = q.front().second;
    q.pop();

    for (vector<Vertex *>::iterator it = v->adj.begin(); it != v->adj.end();
         ++it) {
      Vertex *u = *it;

      if (u->parent == nullptr && v->capacity[u->id] != 0) {
        u->parent = v;
        result_flow = min(previous_flow, v->capacity[u->id]);

        if (u->id == 1) return result_flow;

        q.push(make_pair(u, result_flow));
      }
    }
  }

  return 0;
}

void Graph::solve() {
  int flow;
  Vertex *current, *previous;

  while ((flow = bfs()) != 0) {
    result += flow;
    current = &graph[1];

    while (current->id != 0) {
      previous = current->parent;
      previous->capacity[current->id] -= flow;
      current->capacity[previous->id] += flow;
      current = previous;
    }
  }

  cout << result << endl;
}

int main() {
  int x, y, n, m;

  if (scanf("%d %d\n", &n, &m) == -1) return 1;

  Graph g(n + 2);

  for (int i = 1; i <= n; i++) {
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
