#include<bits/stdc++.h>
#include "hashing_ds.h"
using namespace std;

vector<pair<string,int>> rand_string(int N){
    vector<pair<string,int>> v;
    map<string, int> d;
    int i = 0;
    srand(time(0));
    while(i<N){
        string s;
        for(int j=0; j<7; j++){
            s += 'a' + rand()%26;
        }
        if(d[s] == 0) {
            i++;
            d[s] = i;
            v.push_back({s,i});
        }
    }
    return v;
}


int main(){
    int N ;
    cin >> N;
    vector<pair<string,int>> f;
    f = rand_string(N);

    HashTable HT(N, 1);

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Insert Section\n";

    int i=0;
    while(i < N){
        HT.insert(f[i].first, f[i].second);
        i++;
        if(i%100 == 0){
            if(HT.mx_len() > 5){
                int u = i/10;

                start = chrono::high_resolution_clock::now();
                for(int j=0; j<u; j++){
                    HT.search(f[rand()%i].first);
                }
                end = chrono::high_resolution_clock::now();
                time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                cout << "Before Rehashing time taken : " << time_taken/u << endl; 

                HT.rehash(1);

                start = chrono::high_resolution_clock::now();
                for(int j=0; j<u; j++){
                    HT.search(f[rand()%i].first);
                }
                end = chrono::high_resolution_clock::now();
                time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                cout << "After Rehashing time taken : " << time_taken/u << endl;
            }
        }
    }

    cout << "DELETE SECTION\n";

    i=N-1;
    while(i >= 0){
        HT.remove(f[i].first);
        i--;
        if(i%100 == 0){
            if(HT.mx_len() < 3){
                int u = i/10;

                start = chrono::high_resolution_clock::now();
                for(int j=0; j<u; j++){
                    HT.search(f[rand()%i].first);
                }
                end = chrono::high_resolution_clock::now();
                time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

                cout << "Before Rehashing time taken : " << time_taken/u << endl; 

                HT.rehash(-1);

                start = chrono::high_resolution_clock::now();
                for(int j=0; j<u; j++){
                    HT.search(f[rand()%i].first);
                }
                end = chrono::high_resolution_clock::now();
                time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                cout << "After Rehashing time taken : " << time_taken/u << endl;
            }
        }
    }
}