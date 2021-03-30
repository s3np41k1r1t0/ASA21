#include <iostream>
#include <list>
#include <queue>

using namespace std;

int n,x,y, *incoming, *dist;
list<int> *graph, sources;
queue<int> topological, q;

int main(){
    cin >> n >> x;

		// Space: O(V+E)
		// Time:  O(V+E)
		incoming = new int[n];
		graph = new list<int>[n];
		
    while(cin >> x >> y){
				graph[x-1].push_front(y-1);
				incoming[y-1]++;
		}

		for(int i=0; i<n; i++)
				if(incoming[i] == 0)
						sources.push_front(i);
		
		for(int s: sources)
				q.push(s);

		//Kahn’s algorithm for Topological Sorting
		while(!q.empty()){
				x = q.front();
				q.pop();
				topological.push(x);

				for(int adj: graph[x])
						if(--incoming[adj] == 0)
								q.push(adj);
		}
		
		dist = new int[n];
		y = 0;

		//sssp on a dag - modified
		while(!topological.empty()){
				x = topological.front();
				topological.pop();
							
				for(int adj: graph[x])
						dist[adj] = max(dist[adj],dist[x]+1);
				
				y = max(dist[x],y);
		}

		cout << sources.size() << " " << y+1 << endl;
		
		return 0;
}
