#include<bits/stdc++.h>

using namespace std;

const int INF = 1e7;
const int N = 1000;
typedef long long int ll;

vector<string> names(N);
vector<int> w(N),l(N),r(N),visited(N);
vector<vector<int>> g(N, vector<int>(N,0));

void dfs(int u, vector<int> adj[], vector<vector<int>>& capacity){
    visited[u] = 1;
    for(int e : adj[u]){
        if(!visited[e] && capacity[u][e] > 0) {
            dfs(e, adj, capacity);
        }
    }
}

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

void check_elimination(int x, int n){

    // creating graph
    // teams 1 -> n-1 denotes the teams excluding x in ascending order

    int teams = n-1, combs = (n-1)*(n-2)/2;
    int nodes = teams+combs+2; 
    vector<int> adj[nodes];
    vector<vector<int>> capacity(nodes, vector<int>(nodes,0));
    int s = nodes-2, t = nodes-1;

    // combinations corresponding to teams
    vector<pair<int,int>> comb_betn(combs);
    int k = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(i == x || j == x) continue;
            comb_betn[k++] = make_pair(i,j);
        }
    }

    ll s_out = 0;
    for(int i=0; i<combs; i++){
        adj[s].push_back(i);
        capacity[s][i] = g[comb_betn[i].first][comb_betn[i].second];
        s_out += g[comb_betn[i].first][comb_betn[i].second];

        if(comb_betn[i].first > x) {
            adj[i].push_back(comb_betn[i].first + combs - 1);
            capacity[i][comb_betn[i].first + combs - 1] = INF;
        }
        else {
            adj[i].push_back(comb_betn[i].first + combs);
            capacity[i][comb_betn[i].first + combs] = INF;
        }

        if(comb_betn[i].second > x) {
            adj[i].push_back(comb_betn[i].second + combs - 1);
            capacity[i][comb_betn[i].second + combs - 1] = INF;

        }
        else {
            adj[i].push_back(comb_betn[i].second + combs);
            capacity[i][comb_betn[i].second + combs] = INF;
        }
    }

    int xwin = w[x] + r[x];
    for(int i=combs; i<combs+teams; i++){
        int team_no = i - combs;
        if(team_no >= x) team_no++;
        adj[i].push_back(t);
        capacity[i][t] = xwin - w[team_no];
    }    

    bool res = true;
    int ind = -1;
    for(int i=0; i<n; i++){
        if(w[i] > w[x] + r[x]){
            res = false;
            ind = i;
        }
    }

    if(!res){
        cout << names[x] << " is eliminated.\n";
        cout << "They can win at most " << w[x] << " + " << r[x] << " = " << w[x]+r[x] << " games.\n";
        cout << names[ind] <<  " has won a total of " << w[ind] << " games.\n";
        cout << "They play each other " << 0 << " times.\n";
        cout << "So on average, each of the teams wins " << w[ind] << "/" << 1 << " = " << w[ind] << " games.\n" << endl;

    }
    else if(s_out > maxflow(s, t, nodes, adj, capacity)){
        cout << names[x] << " is eliminated.\n";
        cout << "They can win at most " << w[x] << " + " << r[x] << " = " << w[x]+r[x]  << " games.\n";

        for(int i=0; i<visited.size(); i++) visited[i] = 0;
        dfs(s, adj, capacity);

        // team nodes combs -> combs + teams
        vector<int> vis_teams;
        for(int i=combs; i<combs+teams; i++){
            if(visited[i] == 1){
                int team_no = i - combs;
                if(team_no >= x) team_no++;
                vis_teams.push_back(team_no);
            }
        }

        int match_played = 0;
        for(int i=0; i<vis_teams.size(); i++) {
            match_played += w[vis_teams[i]];
            cout << names[vis_teams[i]];
            if(i != vis_teams.size()-1) cout << ", ";
        }
        cout << " have won a total of " << match_played << " games.\n";

        int ex = 0;
        for(int i=0; i<vis_teams.size(); i++){
            for(int j=i+1; j<vis_teams.size(); j++){
                ex += g[vis_teams[i]][vis_teams[j]];
            }
        }
        cout << "They play each other " << ex << " times.\n";

        cout << "So on average, each of the teams wins " << (match_played+ex) << "/" << vis_teams.size() << " = " << (match_played+ex)*1.0/vis_teams.size() << " games.\n" << endl;
        
    }
    
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        cin >> names[i] >> w[i] >> l[i] >> r[i];
        for(int j=0; j<n; j++) cin >> g[i][j];
    }

    for(int i=0; i<n; i++){
        check_elimination(i, n);
    }

}