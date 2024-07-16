#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll INF = 1e18;


vector<ll> dijkstra(vector<pair<int,ll>> adj[], vector<int>& parent, int s, int n){
    vector<ll> d(n);
    for(int i=0; i<n; i++) d[i] = INF; 
    d[s] = 0;

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0,s});
    parent[s] = s;
    vector<bool> selected(n, false);

    while(!pq.empty()){
        auto mn = pq.top();
        pq.pop();
        int u = mn.second;
        if(selected[u] == true) continue;
        selected[u] = true;
        
        for(int i=0; i<adj[u].size(); i++){
            auto e = adj[u][i];
            if(d[e.first] > d[u] + e.second){
                parent[e.first] = u;
                d[e.first] = d[u] + e.second;
                pq.push({d[e.first], e.first});
            }
        }
    }

    return d;
}

vector<ll> bellmanford(vector<pair<int,ll>> adj[], vector<int>& parent, int s, int n, bool& neg_ccl){
    vector<ll> d(n);
    for(int i=0; i<n; i++) d[i] = INF;
    d[s] = 0;
    parent[s] = s;

    

    for(int i=1; i<=n-1; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<adj[j].size(); k++){
                auto e = adj[j][k];
                if(d[e.first] > d[j] + e.second){
                    d[e.first] = d[j] + e.second;
                    parent[e.first] = j;
                }
            }
        }
    }

    for(int j=0; j<n; j++){
        for(int k=0; k<adj[j].size(); k++){
            auto e = adj[j][k];
            if(d[e.first] > d[j] + e.second){
                neg_ccl = true;
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
    vector<pair<int,ll>> adj[n];
    vector<int> parent(n);
    int u,v;
    double w;
    int neg = 0;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        if(w < 0) neg++;
    }
    int s,d;
    cin >> s >> d;

    if(!neg) {
        vector<ll> sp  = dijkstra(adj, parent, s, n);
        
        if(sp[d] == INF){
            cout << "The destination is not reachable from the given source.\n";
        }
        else {
            cout << "Shortest Path cost : " << sp[d] << endl;
            path_order(parent, d);
        }
    } 
    else {
        bool neg_ccl = false;
        vector<ll> sp = bellmanford(adj, parent, s, n, neg_ccl);

        if(sp[d] == INF){
            cout << "The destination is not reachable from the given source.\n";
        }
        else if(neg_ccl){
            cout << "The graph contains a negative cycle.\n";
        }
        else {
            cout << "The graph does not contain a negative cycle.\n";
            cout << "Shortest Path cost : " << sp[d] << endl;
            path_order(parent, d);
        }
    }   
}