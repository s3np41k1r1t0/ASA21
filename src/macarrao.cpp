#include <iostream>
#include <string.h>
#include <list>

using namespace std;

void debug(list<int> *graph, int n){
		for(int i=0; i<n; i++){
				cout << i << ": ";
				for(auto x = graph[i].begin(); x!=graph[i].end(); x++)
						cout << *x << " ";
				cout << endl;
		}
}

int main(){
    int n,m,x,y;

		// n = #V, m = #E
    cin >> n >> m;

		// Space: O(V+E)
		// Time:  O(V^2+VE)
		list<int> graph[n];
		int incoming[n] = {0};
		list<int> sources, queue;
		int visited, max_seq = 0;

    while(cin >> x >> y){
				graph[x-1].push_front(y-1);
				incoming[y-1]++;
		}

		debug(graph,n);

		for(int i=0; i<n; i++)
				if(incoming[i] == 0)
						sources.push_front(i);
		
		for(int s: sources){
				//should i choose time complexity or space complexity???
				bool temp[n] = {0};
				//memset(temp,0,sizof(int)*n);
				queue.push_front(s);
				visited = 0;
				
				while(!queue.empty()){
						s = queue.front();
						queue.pop_front();	
						for(int adj: graph[s]){
								if(!temp[adj]){
										temp[adj] = 1;
										queue.push_front(adj);
										visited++;
								}
						}
				}

				visited++;
				if(visited > max_seq) max_seq = visited;
		}

		cout << sources.size() << " " << max_seq << endl;

		return 0;
}
