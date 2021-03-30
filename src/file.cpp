#include <iostream>
#include <list>
#include <queue>
#include <cstring>

using namespace std;

typedef int Vertex;

class Graph{
		private:
				Vertex *incoming;
				Vertex *distances;
				list<Vertex> *adj;
				list<Vertex> sources;
				queue<Vertex> topological;
				int size;

				void build_sources();
				void kahn();
				int lssp();

		public:
				Graph(int n);
				void insert(int x, int y);
				void solve();
				void debug();
};

Graph::Graph(int n){
		size = n;
		adj = new list<Vertex>[n];
		distances = new Vertex[n];
		incoming = new Vertex[n];
		memset(incoming,0,size*sizeof(Vertex));
}

void Graph::debug(){
		cout << "GRAPH:" << endl;
		for(int i=0; i<size; i++){
				cout << i+1 << ": ";
				for(auto x: adj[i])
						cout << x+1 << " ";
				cout << endl;
				cout << "INCOMING EDGES: " << incoming[i] << endl;
		}
}

void Graph::insert(int x, int y){
		adj[x-1].push_front(y-1);
		incoming[y-1]++;
}

void Graph::build_sources(){
		for(int i=0; i<size; i++)
				if(incoming[i] == 0)
						sources.push_front(i);
}

void Graph::kahn(){
		queue<int> q;

		build_sources();

		for(Vertex s: sources)
				q.push(s);

		Vertex v;
		while(!q.empty()){
				v = q.front();
				q.pop();
				topological.push(v);

				for(int adj: adj[v])
						if(--incoming[adj] == 0)
								q.push(adj);
		}
}

int Graph::lssp(){
		memset(distances,0,size*sizeof(Vertex));

		//TODO i think this could be optimized
		//i dont think it really needs topological sort to work
		//since we have the sources we can bfs and discover the longest
		//path using the same algorithm
		Vertex v;
		int res = 0;
		while(!topological.empty()){
				v = topological.front();
				topological.pop();

				for(Vertex adj: adj[v])
						distances[adj] = max(distances[adj],distances[v]+1);

				res = max(distances[v],res);
		}

		return res+1;
}

void Graph::solve(){
		//debug();
		kahn();
		int longest = lssp();
		cout << sources.size() << " " << longest << endl;
}

int main(){
		int x,y;

		cin >> x >> y;

		Graph g(x);

		while(cin >> x >> y)
				g.insert(x,y);
		

		g.solve();

		return 0;
}
