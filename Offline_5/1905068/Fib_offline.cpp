#include<bits/stdc++.h>
#include "Fib_ds.h"
using namespace std;
typedef long long int ll;
const ll INF = 1e18;



vector<double> dijkstra_bin_heap(vector<pair<int,double>> adj[], vector<int>& parent, int s, int n){
    vector<double> d(n);
    for(int i=0; i<n; i++) d[i] = INF; 
    d[s] = 0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
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


vector<double> dijkstra_fib_heap(vector<pair<int,double>> adj[], vector<int>& path_sz, int s, int n){
    vector<double> d(n);
    for(int i=0; i<n; i++) d[i] = INF; 
    d[s] = 0;

    FibHeap Fh;
    FibHeapNode* fn =  Fh.insert(0);
    fn->id = s;

    path_sz[s] = 0;
    vector<bool> selected(n, false);

    while(Fh.numOfNodes){
        int u = Fh.extract_min();
        
        if(selected[u] == true) continue;
        selected[u] = true;
        
        for(int i=0; i<adj[u].size(); i++){
            auto e = adj[u][i];
            if(d[e.first] > d[u] + e.second){
                path_sz[e.first] = path_sz[u] + 1;
                d[e.first] = d[u] + e.second;
                FibHeapNode* x = Fh.insert(d[e.first]);
                x->id = e.first;
            }
        }
    }

    return d;
}



int main(){

    freopen("in5.txt","r",stdin);

    int n, m;
    cin >> n >> m;
    vector<pair<int,double>> adj[n];
    vector<int> path_sz(n);
    int u,v;
    double w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }

    freopen("in6.txt","r",stdin);
    int k;
    cin >> k;
    vector<pair<int,int>> v1;
    for(int i=0; i<k; i++) {
        int x,y;
        cin >> x >> y;
        v1.push_back({x,y});
    }

    freopen("E:/out.txt","w",stdout);

    int j = 0;
    while(j < k){
        int s = v1[j].first,d=v1[j].second;
        vector<double> cost;

        auto start = chrono::high_resolution_clock::now();
        cost =  dijkstra_bin_heap(adj, path_sz, s, n);
        auto end = chrono::high_resolution_clock::now();

        cout << cost[d] << "   " << path_sz[d] << "    ";

        cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << "   "; 

        start = chrono::high_resolution_clock::now();
        cost =  dijkstra_bin_heap(adj, path_sz, s, n);
        end = chrono::high_resolution_clock::now();

        cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms"  << endl;  
        
        j++;
    }
}