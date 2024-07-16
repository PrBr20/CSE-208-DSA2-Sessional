#include<bits/stdc++.h>
using namespace std;


vector<int> parent, order;
vector<pair<int,int>> mst;
double ans = 0;

class Edge {
public:
    int u,v;
    double w;
};

bool operator<(Edge const& a, Edge const& b){
    return a.w > b.w;
}

bool compare(Edge const& a, Edge const& b){
    return a.w < b.w;
}

void make_set(int i){
    parent[i] = i;
    order[i] = 0;
}

int find_set(int u){
    if(parent[u] != u){
        parent[u] = find_set(parent[u]);
    }
    return parent[u];
}

void union_set(int u, int v){
    int up = parent[u], vp = parent[v];
    if(up != vp){
        if(order[up] > order[vp]) swap (order[up], order[vp]);
        parent[up] = vp;
        if(order[up] == order[vp]) order[vp]++;
    }
}

void kruskal(vector<Edge>& edges, int n, int m){
    sort(edges.begin(), edges.end(), compare);

    parent.resize(n);
    order.resize(n);

    for(int i=0; i<n; i++) make_set(i);

    for(int i=0; i<m; i++){
        if(find_set(edges[i].u) != find_set(edges[i].v)){
            union_set(edges[i].u, edges[i].v);
            ans += edges[i].w;
            mst.push_back({edges[i].u,edges[i].v});
        }
    }
}


void prims(vector<pair<int,double>> adj[], int n){
    priority_queue<Edge, vector<Edge>> pq;
    vector<bool> selected(n, false);
    pq.push({0,0,0});

    while(!pq.empty()){
        Edge h = pq.top();
        pq.pop();

        int new_node;
        if(!selected[h.u]) new_node = h.u;
        else if(!selected[h.v]) new_node = h.v;
        else continue;

        selected[new_node] = true;
        ans += h.w;
        if(h.u != h.v) mst.push_back({h.u,h.v});

        for(auto e : adj[new_node]){
            if(!selected[e.first]){
                pq.push({new_node,e.first,e.second});
            }
        }
    }
}

int main(){
    // reading input from file
    freopen("mst.in","r",stdin);

    int n,m;
    cin >> n >> m;
    
    vector<Edge> edges;
    vector<pair<int,double>> adj[n];
    for(int i=0; i<m; i++){
        int x,y;
        double w;
        cin >> x >> y >> w; 
        edges.push_back({x,y,w});
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }
    

    prims(adj, n);
    cout << "Cost of the minimum spanning tree : " << ans << endl;

    cout << "List of edges selected by Prim's: {";
    for(int i=0; i<mst.size(); i++){
        cout << "(" << mst[i].first << "," << mst[i].second << ")";
        if(i!=mst.size()-1) cout << ",";
    }
    cout << "}" << endl;

    mst.clear();

    kruskal(edges, n, m);
    cout << "List of edges selected by Kruskal's: {";
    for(int i=0; i<mst.size(); i++){
        cout << "(" << mst[i].first << "," << mst[i].second << ")";
        if(i!=mst.size()-1) cout << ",";
    }
    cout << "}" << endl;

}