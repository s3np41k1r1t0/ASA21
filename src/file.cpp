#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class Graph{
	private:
		class Vertex{
			public:
				vector<Vertex*> adj;
				unsigned int distance = 0;
				unsigned int incoming = 0;
		};
		Vertex *graph;
		queue<Vertex*> topological;
		queue<Vertex*> queque;
		unsigned int size;

		unsigned int kahn();
		unsigned int lssp();

	public:
		Graph(unsigned int n);
		void insert(unsigned int x, unsigned int y);
		void solve();
};
			
Graph::Graph(unsigned int n){
	size = n;
	graph = new Vertex[n];
}

void Graph::insert(unsigned int x, unsigned int y){
	graph[x-1].adj.push_back(&graph[y-1]);
	graph[y-1].incoming++;
}

unsigned int Graph::kahn(){
	Vertex *v;
	unsigned int res;
	vector<Vertex*>::iterator idx;

	for(unsigned int i=0; i<size; i++)
		if(graph[i].incoming == 0)
			queque.push(&graph[i]);

	res = queque.size();

	while(!queque.empty()){
		v = queque.front();
		queque.pop();
		topological.push(v);

		for(idx = v->adj.begin(); idx != v->adj.end(); idx++)
			if(--(*idx)->incoming == 0)
				queque.push(*idx);
	}

	return res;
}

unsigned int Graph::lssp(){
	Vertex *v;
	unsigned int res = 0;
	vector<Vertex*>::iterator idx;

	while(!topological.empty()){
		v = topological.front();
		topological.pop();

		for(idx = v->adj.begin(); idx != v->adj.end(); idx++)
			if(v->distance+1 > (*idx)->distance)
				(*idx)->distance = v->distance+1;
		
		if(v->distance > res)
			res = v->distance;
	}

	return res+1;
}

void Graph::solve(){
	int k = kahn();
	int l = lssp();
	printf("%d %d\n",k,l);
}

int main(){
	unsigned long m;
	unsigned int x,y,n;

	if(scanf("%d %lu\n",&n,&m) == -1)
		return 1;

	Graph g(n);

	while(scanf("%d %d\n",&x,&y) != -1)
		g.insert(x,y);

	g.solve();

	return 0;
}
