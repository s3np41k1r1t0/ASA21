#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Dominos {
    public:
        vector<vector<int>> graph;
        map<int,bool> colors;
        list<int> stack;
        int visited;
        int minimo_pecas = 0, max_seq = 0;
        bool build;

        Dominos(int n): graph(n){}

        void insert_graph(int i, int v);
        void debug();
        void DFS_visit(int v);
        void build_topological_order();
        void solve();
        void print_answers();
};

void Dominos::insert_graph(int i, int v){
    graph[i-1].push_back(v-1);
}

void Dominos::debug(){
    cout << "GRAPH: " << endl;

    for(int i=0; i < (int)graph.size(); i++){
        cout << i+1 << ": ";
        for(auto x = graph[i].begin(); x != graph[i].end(); x++)
            cout << (*x)+1 << " ";
        cout << "\n";
    }

    cout << "STACK: ";

    for(auto i = stack.begin(); i != stack.end(); i++)
        cout << (*i)+1 << " ";

    cout << endl;
}

void Dominos::DFS_visit(int v){
    colors[v] = true;

    for(vector<int>::iterator adj = graph[v].begin(); adj != graph[v].end(); adj++){
        if(colors[*adj] == false){
            DFS_visit(*adj);
        }
    }

    if(build) stack.push_front(v);
    visited++;
}

void Dominos::build_topological_order(){
    stack.clear();
    colors.clear();
    build = true;

    for(int v = 0; v < (int)graph.size(); v++)
        if(colors[v] == false)
            DFS_visit(v);
}

void Dominos::solve(){
    minimo_pecas = 0, max_seq = 0;
    colors.clear();
    build = false;

    while(!stack.empty()){
        int v = stack.front();
        stack.pop_front();

        if(colors[v] == false){
            visited = 0;
            DFS_visit(v);
            minimo_pecas++;
            if(visited > max_seq) max_seq = visited;
        }
    }
}

void Dominos::print_answers(){
    cout << minimo_pecas << " " << max_seq << endl;
}

int main(){
    int n,m,x,y;

    cin >> n >> m;

    Dominos graph(n);

    //build graph
    while(cin >> x >> y)
        graph.insert_graph(x,y);

    graph.build_topological_order();
    //graph.debug();
    graph.solve();
    graph.print_answers();

    return 0;
}
