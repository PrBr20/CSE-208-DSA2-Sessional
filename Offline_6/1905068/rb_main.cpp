#include<bits/stdc++.h>
#include "rb_ds.cpp"
using namespace std;

int main(){
    freopen("in.txt", "r", stdin);
    RB_Tree T;
    int n;
    cin >> n;
    while(n--){
        int e,x;
        cin >> e >> x;

        if(e == 0){
            if(T.rb_find(x) == T.nil) cout << e << " " << x << " " << 0 << endl;
            else {
                T.rb_delete(x);
                cout << e << " " << x << " " << 1 << endl;
            }
        }
        else if(e == 1){
            if(T.rb_find(x) != T.nil) cout << e << " " << x << " " << 0 << endl;
            else {
                T.rb_insert(x);
                cout << e << " " << x << " " << 1 << endl;
            }
        }
        else if(e == 2){
            if(T.rb_find(x) == T.nil) cout << e << " " << x << " " << 0 << endl;
            else cout << e << " " << x << " " << 1 << endl;
        }
        else if(e == 3){
            cout << e << " " << x << " " << T.lessThanX(x) << endl;
        }
    }
}
