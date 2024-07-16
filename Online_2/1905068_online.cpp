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
            //ans += edges[i].w;
            mst.push_back({edges[i].u,edges[i].v});
        }
    }
}


int main(){
    // reading input from file
    //freopen("mst.in","r",stdin);

    int n,m;
    cin >> n >> m;

    vector<Edge> edgesm, edgesf;
    int e1 = 0, e2 = 0;
    for(int i=0; i<m; i++){
        int x,y;
        double w;
        cin >> x >> y >> w;
        if(w == 3){
            edgesm.push_back({x,y,1});
            edgesf.push_back({x,y,1});
            e1+=1;
            e2+=1;
        }
        else if(w == 1) {
            edgesm.push_back({x,y,2});
            e1+=1;
        }
        else {
            edgesf.push_back({x,y,2});
            e2+=1;
        }
    }



    vector<pair<int,int>> m1, m2;
    vector<bool> selected(n,false);
    bool res = true;

    kruskal(edgesm, n, e1);
    m1 = mst;

    for(int i=0; i<m1.size(); i++){
        selected[mst[i].first] = true;
        selected[mst[i].second] = true;
    }
    for(int i=0; i<n; i++){
        if(selected[i] == false) res = false;
    }
    for(int i=0; i<n; i++){
        selected[i] = false;
    }

    mst.clear();
    kruskal(edgesf, n, e2);
    m2 = mst;

    for(int i=0; i<m2.size(); i++){
        selected[mst[i].first] = true;
        selected[mst[i].second] = true;
    }
    for(int i=0; i<n; i++){
        if(selected[i] == false) res = false;
    }

    for(int i=0; i<m1.size(); i++){
        cout << m1[i].first << " " << m1[i].second << endl;
    }
    for(int i=0; i<m2.size(); i++){
        cout << m2[i].first << " " << m2[i].second << endl;
    }

    if(res == false){
        cout << -1 << endl;
    }
    else {
        set<pair<int,int>> s;
        for(int i=0; i<m1.size(); i++){
            s.insert({m1[i].first,m1[i].second});
        }
        for(int i=0; i<m1.size(); i++){
            s.insert({m2[i].first,m2[i].second});
        }

        cout << n-s.size() << endl;
    }

}
