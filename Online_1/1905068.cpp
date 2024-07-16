#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.size();
    vector<int> g[n+1];

    for(int i=1; i<n; i++){
        g[i].push_back(i+1);
    }

    for(int i=0; i<10; i++){
        int prev = -1;
        for(int j=0; j<n; j++){
            if(i+'0' == s[j]) {
                if(prev == -1) prev = j+1;
                else {
                    if(g[prev].back() == j+1) g[prev].pop_back();
                    g[prev].push_back(j+1);
                }
            }
        }
    }

    queue<int> q;
    q.push(1);
    bool vis[n+1];
    for(int i=0; i<n; i++) vis[i] = false;

    int len[n+1];
    for(int i=0; i<=n; i++) len[i] = 0;
    len[1] = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = true;

        for(int i=0; i<g[u].size(); i++){
            if(!vis[g[u][i]]){
                q.push(g[u][i]);
                len[g[u][i]] = len[u] + 1;
            }
        }
    }

    cout << len[n] << endl;

}
