#include <iostream>
#include <vector>

using namespace std;

void debug(vector<vector<int>> &graph){
    for(int i=0; i < (int)graph.size(); i++){
        cout << i+1 << ": ";
        for(auto x = graph[i].begin(); x != graph[i].end(); x++)
            cout << (*x)+1 << " ";
        cout << "\n";
    }
}



int main(){
    int n,m,x,y;

    cin >> n >> m;

    vector<vector<int>> graph(n);

    while(cin >> x >> y){
       graph[x-1].push_back(y-1);
    }

    debug(graph);

    return 0;
}
