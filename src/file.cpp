#include <iostream>
#include <forward_list>
#include <queue>
#include <cstring>

using namespace std;

class Vertex{
	public:
		forward_list<Vertex*> adj;
		unsigned int distance = 0;
		unsigned int incoming = 0;
		void create_edge(Vertex *e);
};

void Vertex::create_edge(Vertex *e){
	adj.push_front(e);
}

class Graph{
	private:
		Vertex *graph;
		queue<Vertex*> topological;
		queue<Vertex*> q;
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
	graph[x-1].create_edge(&graph[y-1]);
	graph[y-1].incoming++;
}

unsigned int Graph::kahn(){
	Vertex *v;
	unsigned int res;
	forward_list<Vertex*>::iterator idx;

	for(unsigned int i=0; i<size; i++)
		if(graph[i].incoming == 0)
			q.push(&graph[i]);

	res = q.size();

	while(!q.empty()){
		v = q.front();
		q.pop();
		topological.push(v);

		for(idx = v->adj.begin(); idx != v->adj.end(); idx++)
			if(--(*idx)->incoming == 0)
				q.push(*idx);
	}

	return res;
}

unsigned int Graph::lssp(){
	//TODO i think this could be optimized
	//i dont think it really needs topological sort to work
	//since we have the sources we can bfs and discover the longest
	//path using the same algorithm
	Vertex *v;
	unsigned int res = 0;
	forward_list<Vertex*>::iterator idx;

	while(!topological.empty()){
		v = topological.front();
		topological.pop();

		for(idx = v->adj.begin(); idx != v->adj.end(); idx++)
			(*idx)->distance = max((*idx)->distance,v->distance+1);

		res = max(v->distance,res);
	}

	return res+1;
}

void Graph::solve(){
	if(size > 0)
		cout << kahn() << " " << lssp() << endl;
	else
		cout << "0 0\n";
}

int main(){
	long m;
	int x,y,n;

	cin >> n >> m;

	if(n <= 0 || m <= 0)
		return 1;

	Graph g(n);

	while(cin >> x >> y && --m)
		if(x > 0 && y > 0 && x <= n && y <= n)
			g.insert(x,y);
		else
			return 1;

	g.solve();

	return 0;
}
