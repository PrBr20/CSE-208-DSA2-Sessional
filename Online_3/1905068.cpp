#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll INF = 1e18;

vector<double> bellmanford(vector<pair<int,double>> adj[], vector<int>& parent, int s, int n){
    vector<double> d(n);
    for(int i=0; i<n; i++) d[i] = 0;
    d[s] = 1;
    parent[s] = s;

    for(int i=1; i<=n-1; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<adj[j].size(); k++){
                auto e = adj[j][k];
                if(d[e.first] < d[j] * e.second){
                    d[e.first] = d[j] * e.second;
                    parent[e.first] = j;
                }
            }
        }
    }

    return d;
}

void path_order(vector<int>& parent, int d){
    vector<int> path;
    path.push_back(d);
    while(parent[d] != d){
        d = parent[d];
        path.push_back(d);
    }
    reverse(path.begin(), path.end());
    for(int i=0; i<path.size(); i++){
        cout << path[i];
        if(i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<int,double>> adj[n];
    vector<int> parent(n);
    int u,v;
    double w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }
    int s,d;
    cin >> s >> d;

    vector<double> sp  = bellmanford(adj, parent, s, n);

    if(sp[d] == 0 && d!=s){
        cout << "The path from the source to destination is not reliable at all.\n";
    }
    else {
        cout << "Most reliable path score: " << sp[d] << endl;
        path_order(parent, d);
    }
}
