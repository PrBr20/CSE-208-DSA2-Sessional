#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll INF = 1e17;

vector<vector<ll>> mat_mul(vector<vector<ll>> weight, int n){
    vector<vector<ll>> w_prev = weight;
    for(int i=2; i<=n-1; i++){
        vector<vector<ll>> w_tmp(n+1, vector<ll>(n+1, INF));
        for(int i=1; i<=n; i++) w_tmp[i][i] = 0;

        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                for(int l=1; l<=n; l++) {
                    w_tmp[j][k] = min(w_tmp[j][k], w_prev[j][l] + weight[l][k]);
                }
            }
        }

        for(int j=0; j<=n; j++){
            for(int k=0; k<=n; k++){
                w_prev[j][k] = w_tmp[j][k];
            }
        }
    }

    return w_prev;
}


vector<vector<ll>> floy_war(vector<vector<ll>> weight, int n){
    vector<vector<ll>> w_prev = weight;

    for(int i=1; i<=n; i++){
        vector<vector<ll>> w_tmp(n+1, vector<ll>(n+1, INF));
        for(int i=1; i<=n; i++) w_tmp[i][i] = 0;

        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                w_tmp[j][k] = min(w_prev[j][k], w_prev[j][i] + w_prev[i][k]);
            }
        }

        for(int j=0; j<=n; j++){
            for(int k=0; k<=n; k++){
                w_prev[j][k] = w_tmp[j][k];
            }
        }
    }

    return w_prev;
}





int main(){
    int n,m;
    cin >> n >> m;

    vector<vector<ll>> weight(n+1, vector<ll>(n+1, INF));
    for(int i=1; i<=n; i++) weight[i][i] = 0;


    for(int i=0; i<m; i++){
        int x,y,w;
        cin >> x >> y >> w;
        weight[x][y] = w; 
    }

    vector<vector<ll>> mat = mat_mul(weight, n);

    cout << "Shortest distance matrix\n";
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++) {
            if(mat[i][j] != INF) cout << mat[i][j] << " ";
            else cout << "INF" << " ";
        }
        cout << endl;
    }

}