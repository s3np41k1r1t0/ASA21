#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
	private:
		class Vertex{
			public:
				unsigned int id = 0;
				Vertex* parent = nullptr;
				unsigned int rank = 0;
				short g = -1;
				
				// O(?)
				Vertex* findSet() {
					if(parent == nullptr) return this;
					
					if(parent->parent != nullptr){
						parent = parent->findSet();
					}

					return parent;
				}

				// O(M) <- compressao de caminho
				void Union(Vertex* v){
					Vertex* rx = this->findSet();
					Vertex* ry = v->findSet();
					
					if(rx->id == ry->id) return;
					
					if(rx->rank > ry->rank){
						ry->parent = rx;
					} else if(ry->rank > rx->rank){
						rx->parent = ry;
					} else {
						ry->parent = rx;
						rx->rank += 1;
					}
				};
		};
		
		class Edge{
			public:
				unsigned int cost;
				Vertex *v1, *v2; 
				
				Edge(unsigned int cost, Vertex& v1, Vertex& v2){
					this->cost = cost;
					this->v1 = &v1;
					this->v2 = &v2;
				}
		};

		Vertex* graph;
		vector<Edge> edges;
		vector<Vertex*> xadj;
		vector<Vertex*> yadj;
		unsigned int *xcost, *ycost;
		unsigned int size;
		unsigned int result = 0;

	public:
		Graph(unsigned int n);
		void insert(unsigned int x, unsigned int y, unsigned int cost);
		void insertX(unsigned int v, unsigned int cost);
		void insertY(unsigned int v, unsigned int cost);
		void solve();
		void prim();
		bool static edgeCostComparator(Edge& e1, Edge& e2);
		bool static edgeVertexComparator(Edge& e1, Edge& e2);
};

// O(V)
Graph::Graph(unsigned int n){
	size = n;
	graph = new Vertex[n];
	xcost = new unsigned int[n-2];
	ycost = new unsigned int[n-2];
	
	for(unsigned int i = 0; i < n; i++){
		graph[i].id = i;
	}
}

// O(1)
void Graph::insert(unsigned int x, unsigned int y, unsigned int cost){
	//graph[x+1].adj.push_back(&graph[y+1]);
	//graph[y+1].adj.push_back(&graph[x+1]);
	edges.push_back(Edge(cost,graph[x+1],graph[y+1]));
}

// O(1)
void Graph::insertX(unsigned int v, unsigned int cost){
	xadj.push_back(&graph[v+1]);
	xcost[v-1] = cost;
	edges.push_back(Edge(cost,graph[0],graph[v+1]));
}

// O(1)
void Graph::insertY(unsigned int v, unsigned int cost){
	yadj.push_back(&graph[v+1]);
	ycost[v-1] = cost;
	edges.push_back(Edge(cost,graph[1],graph[v+1]));
}

// ElogE
void Graph::prim(){
	vector<Edge> mst;

	// ElogE
	sort(edges.begin(),edges.end(),edgeCostComparator);

	// O(E m)?
	for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++){
		Edge u = *it;
		if(u.v1->findSet()->id != u.v2->findSet()->id){
			u.v1->Union(u.v2);
			mst.push_back(u);
		}
	}

	// NlogN
	sort(mst.begin(),mst.end(),edgeVertexComparator);
	
	for(vector<Edge>::iterator it = mst.begin(); it != mst.end(); it++){
		Edge u = *it;
		if(u.v1->id == 0){
			u.v2->g = 0;
		} else if(u.v1->id == 1){
			u.v2->g = 1;
		} else if(u.v2->id == 0){
			u.v1->g = 0;
		} else if(u.v2->id == 1){
			u.v1->g = 1;
		} else if(u.v1->g != -1){
			if(u.v1->g == 0){
				if(ycost[u.v2->id-2] + u.cost < xcost[u.v2->id-2]){
					u.v2->g = 1;
					result += u.cost;
				} else {
					u.v2->g = 0;
				}
			} else {
				if(xcost[u.v2->id-2] + u.cost < ycost[u.v2->id-2]){
					u.v2->g = 0;
					result += u.cost;
				} else {
					u.v2->g = 1;
				}
			}
		} else if(u.v2->g != -1){
			if(u.v2->g == 0){
				if(ycost[u.v1->id-2] + u.cost < xcost[u.v1->id-2]){
					u.v1->g = 1;
					result += u.cost;
				} else {
					u.v1->g = 0;
				}
			} else {
				if(xcost[u.v1->id-2] + u.cost < ycost[u.v1->id-2]){
					u.v1->g = 0;
					result += u.cost;
				} else {
					u.v1->g = 1;
				}
			}
		}
	}
}

void Graph::solve(){
	prim();
	
	for(vector<Vertex*>::iterator i = xadj.begin(); i != xadj.end(); i++)
		if((*i)->g == 0) result += xcost[(*i)->id-2];

	for(vector<Vertex*>::iterator i = yadj.begin(); i != yadj.end(); i++)
		if((*i)->g == 1) result += ycost[(*i)->id-2];
		
	cout << result << endl;
}

bool Graph::edgeCostComparator(Edge& e1, Edge& e2){
	return e1.cost < e2.cost;
}

bool Graph::edgeVertexComparator(Edge& e1, Edge& e2){
	return (e1.v1->id < e1.v2->id ? e1.v1->id : e1.v2->id) < (e2.v1->id < e2.v2->id ? e2.v1->id : e2.v2->id);
}

int main(){
	unsigned int x,y,n,m;
	
	if(scanf("%d %d\n",&n,&m) == -1) return 1;

	Graph g(n+2);
	
	for(unsigned int i = 1; i <= n; i++){
		if(scanf("%d %d\n",&x,&y) == -1) return 1;
		g.insertX(i,x);
		g.insertY(i,y);
	}

	for(unsigned int i = 0; i < m; i++){
		if(scanf("%d %d %d\n",&x,&y,&n) == -1) return 1;
		g.insert(x,y,n);
	}

	g.solve();

	return 0;
}
