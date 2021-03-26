#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

//void Dominos::debug(){
//    cout << "GRAPH: " << endl;
//
//    for(unsigned int i=0; i < size; i++){
//        cout << i+1 << ": ";
//        for(auto x = graph[i].begin(); x != graph[i].end(); x++)
//            cout << (*x)+1 << " ";
//        cout << "\n";
//    }
//
//    cout << "STACK: ";
//
//    for(auto i = stack.begin(); i != stack.end(); i++)
//        cout << (*i)+1 << " ";
//
//    cout << endl;
//}

//void Dominos::build_topological_order(){
//    stack.clear();
//    clear_visited();
//    build = true;
//
//    for(unsigned int v = 0; v < size; v++)
//        if(graph[v].visited == false)
//            DFS_visit(graph[v]);
//}

class Dominos {
    public:
        vector<vector<int>> graph;
        list<int> stack;
				map<int,bool> colors;

        int visited;
        int minimo_pecas, max_seq;
        bool build;

        Dominos(unsigned int n): graph(n){}

        void insert_graph(int i, int v);
        //void debug();
        void DFS_visit(int v);
        void solve();
        void print_answers();
};

void Dominos::insert_graph(int i, int v){
    graph[i-1].push_back(v-1);
}

void Dominos::DFS_visit(int v){
		colors[v] = true;
    
    for(auto adj = graph[v].begin(); adj != graph[v].end(); adj++){
        if(colors[*adj] == false){
            DFS_visit(graph[v][*adj]);
        }
    }

    visited++;
}

void Dominos::solve(){
		map<int,int> incoming;
		for(int x = 0; x < (int) graph.size(); x++)
				for(auto y = graph[x].begin(); y != graph[x].end(); y++)
						incoming[x]++;

		vector<int> sources;
		for(int x = 0; x < (int)graph.size(); x++)
				if(incoming[x] == 0)
						sources.push_back(x);

		minimo_pecas = sources.size();

		for(int i = 0; i < (int)sources.size(); i++){
				colors.clear();
				visited = 0;
				DFS_visit(sources[i]);
				if(visited > max_seq) max_seq = visited;
		}
}

void Dominos::print_answers(){
    cout << minimo_pecas << " " << max_seq << endl;
}


int main(){
    int n,m,x,y;

    cin >> n >> m;

    Dominos dominos(n);

    //build dominos
    while(cin >> x >> y)
        dominos.insert_graph(x,y);

    //dominos.build_topological_order();
    //dominos.debug();
    dominos.solve();
    dominos.print_answers();

    return 0;
}
