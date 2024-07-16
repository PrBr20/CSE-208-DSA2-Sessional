#include<bits/stdc++.h>

using namespace std;

pair<vector<string>, int> F;

void print_mat(vector<string>& mat){
    int n = mat.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << mat[i][j] ;
        }
        cout << endl;
    }
    cout << endl;
}

int lower_bound(vector<string> mat, int fxr, int fxc){
    int n = mat.size();
    int lb = -1;

    // unfixed portion
    for(int i=fxc; i<n; i++){
        int cnt = 0;
        for(int j=0; j<n; j++){
            if(mat[j][i] == 'X') cnt++;
        }
        lb = max(lb, (cnt+1)/2);
    }

    for(int i=fxr; i<n; i++){
        int cnt = 0;
        for(int j=0; j<n; j++){
            if(mat[i][j] == 'X') cnt++;
        }
        lb = max(lb, (cnt+1)/2);
    }


    //fixed portion
    for(int i=0; i<fxc; i++){
        int cnt = 0;
        for(int j=fxr; j<n; j++){
            if(mat[j][i] == 'X') cnt++;
        }
        if(cnt) lb = max(lb, cnt + fxr - i);
    }

    for(int i=0; i<fxr; i++){
        int cnt = 0;
        for(int j=fxc; j<n; j++){
            if(mat[i][j] == 'X') cnt++;
        }
        if(cnt) lb = max(lb, cnt + fxc - i);
    }

    //inside fixed region
    for(int i=0; i<fxr; i++){
        for(int j=0; j<fxc; j++){
            if(mat[i][j] == 'X'){
                lb = max(lb, abs(i-j) + 1);
            }
        }
    }
    
    return lb;
}

void band_mat(pair<vector<string>, int> matp, int fxr, int fxc){

        vector<string> mat_org = matp.first;
        int n = mat_org.size();

        if(fxr == n-1 && fxc == n-1){
            
            if(lower_bound(mat_org, fxr, fxc) < F.second){
                F.first = mat_org;
                F.second = lower_bound(mat_org, fxr, fxc);
            }

        }
        else {
            vector<pair<vector<string>, int>> lb_mats; 
            int lb = n+1;

            if(fxr == fxc){
                for(int i=fxc; i<n; i++){
                    vector<string> mat = mat_org;

                    for(int j=i; j>=fxc+1; j--){
                        for(int k=0; k<n; k++){
                            swap(mat[k][j], mat[k][j-1]);
                        }
                    }
                    
                    int new_lb = lower_bound(mat, fxr, fxc+1);
                
                    if(new_lb < lb){
                        lb = new_lb;
                        lb_mats.clear();
                        lb_mats.push_back({mat, lb});
                    }
                    else if(new_lb == lb){
                        lb_mats.push_back({mat, lb});
                    }
                }
                fxc++;
            }
            else {
                for(int i=fxr; i<n; i++){
                    vector<string> mat = mat_org;

                    for(int j=i; j>=fxr+1; j--){
                        swap(mat[j], mat[j-1]);
                    }

                    int new_lb = lower_bound(mat, fxr+1, fxc);
                    if(new_lb < lb){
                        lb = new_lb;
                        lb_mats.clear();
                        lb_mats.push_back({mat, lb});
                    }
                    else if(new_lb == lb){
                        lb_mats.push_back({mat, lb});
                    }
                }
                fxr++;
            }
     
            for(int i=0; i<lb_mats.size(); i++){
                if(lb_mats[i].second < F.second){
                    band_mat(lb_mats[i], fxr, fxc);
                }
            }
        }
    
}


int main(){
    int n;
    cin >> n;

    vector<string> mat(n);
    for(int i=0; i<n; i++) cin >> mat[i];

    cout << endl;

    F = {mat, n+1};
 
    band_mat({mat, lower_bound(mat, 0 , 0)}, 0, 0);

    cout << F.second << endl;
    print_mat(F.first);
}