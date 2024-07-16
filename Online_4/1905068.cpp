#include<bits/stdc++.h>

using namespace std;

const int INF = 1e7;
const int N = 1000;
typedef long long int ll;

vector<string> s1(N), s2(N);
vector<string> sizes = {"XXL", "XL", "L", "M", "S", "XS"};

int bfs(int s, int t, vector<int>& parent, vector<int> adj[], vector<vector<int>>& capacity) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;

        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n, vector<int> adj[], vector<vector<int>>& capacity) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int check_graph(int n, int m){
    int nodes = m + n*6 + 2;
    int s = nodes - 2, t = nodes - 1;

    vector<int> adj[nodes];
    vector<vector<int>> capacity(nodes, vector<int>(nodes, 0));

    for(int i=0; i<m; i++){
        adj[s].push_back(i);
        capacity[s][i] = 1;
    }

    int shirts = n*6;

    for(int i=0; i<m; i++){
        for(int j=0; j<shirts; j++){
            if(s1[i] == sizes[j%6] || s2[i] == sizes[j%6]){
                adj[i].push_back(j+m);
                capacity[i][j+m] = 1;
            }
        }
    }

    for(int j=0; j<shirts; j++){
        adj[j+m].push_back(t);
        capacity[j+m][t] = 1;
    }

    return maxflow(s, t, nodes, adj, capacity);
}


int main(){
    int t;
    cin >> t;
    int f = 1;
    while(f <= t){
        int n, m;
        cin >> n >> m;

        for(int i=0; i<m; i++){
            cin >> s1[i] >> s2[i];
        }

        if(check_graph(n, m) == m){
            cout << "Case " << f << ": " << "YES\n";
        }
        else cout << "Case " << f << ": " << "NO\n";
        f++;
    }

}

// bipartite matching n*6 shirts will connect to sink and m contestants and their connecting source



// for each contestant there are n*2 shirts available
