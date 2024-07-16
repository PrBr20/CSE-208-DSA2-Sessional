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

string make_str1(string s){
    int g = s.size();
    string h(max(25-g,0), ' ');
    return s+h;

}

string make_str2(string s){
    int g = s.size();
    string h(max(50-g,0), ' ');
    return s+h;
}


void output_table(int N, int type, vector<pair<string, int>>& f){
    HashTable HT(N, type);

    int i = 0;
    int cnt = 0;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    if(type == 1) cout << make_str1(" ") <<  make_str1("Before Deletion") << make_str1("After Deletion") << "\n";
    else cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
    if(type == 1) cout << make_str1("Load Factor") << make_str1("Avg search time") << make_str1("Avg search time") << "\n";
    else cout << make_str1("Load Factor") <<  make_str1("Avg search time") << make_str1("Avg number of probes") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";

    vector<int> ff;
    while(i < N){
        bool g = HT.insert(f[i].first, f[i].second);
        i++;
        if((HT.loadFactor() >= 0.4 && cnt == 0) || (HT.loadFactor() >= 0.5 && cnt == 1) || (HT.loadFactor() >= 0.6 && cnt == 2) || (HT.loadFactor() >= 0.7 && cnt == 3) || (HT.loadFactor() >= 0.8 && cnt == 4) || (HT.loadFactor() >= 0.9 && cnt == 5)){


            if(cnt == 0) cout << make_str1("0.4") ;
            else if(cnt == 1) cout << make_str1("0.5");
            else if(cnt == 2) cout << make_str1("0.6");
            else if(cnt == 3) cout << make_str1("0.7");
            else if(cnt == 4) cout << make_str1("0.8");
            else if(cnt == 5) cout << make_str1("0.9");

            int u = i/10;


            start = chrono::high_resolution_clock::now();

            long long int tot_prob = 0;
            for(int j=0; j<u; j++){
                int r = rand()%i;
                HT.search(f[r].first);
                tot_prob += HT.getProbe();
            }


            end = chrono::high_resolution_clock::now();
            time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            if(type == 1) cout << make_str1(to_string(time_taken*1.0/u));
            else {
                cout << make_str1(to_string(time_taken*1.0/u));
                cout << make_str1(to_string(tot_prob*1.0/u)) ;
            }


            int k = 0;

            vector<int> s1, s2;

            for(int j=0; j<i; j++){
                int r = rand()%2;

                if(r==0 && k<u){
                    s1.push_back(j);
                    HT.remove(f[j].first);
                    k++;
                }
                else{
                    s2.push_back(j);
                }
            }

            int j = 0, m1 = s1.size();
            vector<int> ns;
            for(; j<u/2; j++){
                int r = rand()%m1;

                ns.push_back(s1[r]);
            }

            int m2 = s2.size();
            for(; j<u; j++){
                int r = rand()%m2;
                ns.push_back(s2[r]);
            }


            start = chrono::high_resolution_clock::now();

            tot_prob = 0;
            for(int j=0; j<ns.size(); j++){
                HT.search(f[ns[j]].first);
                tot_prob += HT.getProbe();
            }


            end = chrono::high_resolution_clock::now();
            time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            if(type == 1) cout << make_str1(to_string(time_taken*1.0/u)) << "\n";
            else{
                cout << make_str1(to_string(time_taken*1.0/u));
                cout << make_str1(to_string(tot_prob*1.0/u)) << "\n";
            }


            /*for(int j=0; j<s1.size(); j++){
                HT.insert(f[s1[j]].first, f[s1[j]].second);
            }*/
            cnt++;
        }
        if(HT.loadFactor() >= 0.9) break;
    }

}

void helper1(HashTable& HT, int type, int i, vector<pair<string, int>>& f){
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    if(type == 1){
        cout << make_str1("Separate Chaining");
    }
    else if(type == 2){
        cout << make_str1("Linear Probing");
    }
    else if(type == 3){
        cout << make_str1("Quadratic Probing");
    }
    else cout << make_str1("Double Hashing");

    int u = i/10;

    start = chrono::high_resolution_clock::now();

    long long int tot_prob = 0;
    for(int j=0; j<u; j++){
        int r = rand()%i;
        HT.search(f[r].first);
        tot_prob += HT.getProbe();
    }

    end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << make_str1(to_string(time_taken*1.0/u));
    if(type != 1) cout << make_str1(to_string(tot_prob*1.0/u)) ;
    else cout << make_str1("N/A");

    int k = 0;
    vector<int> s1, s2;

    for(int j=0; j<i; j++){
        int r = rand()%2;

        if(r==0 && k<u){
            s1.push_back(j);
            HT.remove(f[j].first);
            k++;
        }
        else{
            s2.push_back(j);
        }
    }

    int j = 0, m1 = s1.size();
    vector<int> ns;
    for(; j<u/2; j++){
        int r = rand()%m1;

        ns.push_back(s1[r]);
    }

    int m2 = s2.size();
    for(; j<u; j++){
        int r = rand()%m2;
        ns.push_back(s2[r]);
    }

    start = chrono::high_resolution_clock::now();

    tot_prob = 0;
    for(int j=0; j<ns.size(); j++){
        HT.search(f[ns[j]].first);
        tot_prob += HT.getProbe();
    }

    end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << make_str1(to_string(time_taken*1.0/u));
    if(type != 1) cout << make_str1(to_string(tot_prob*1.0/u)) << "\n";
    else cout << make_str1("N/A") << "\n";

    for(int j=0; j<s1.size(); j++){
        HT.insert(f[s1[j]].first, f[s1[j]].second);
    }
}


void output_table2(int N, vector<pair<string,int>>& f){
    HashTable HT1(N, 1);
    HashTable HT2(N, 2);
    HashTable HT3(N, 3);
    HashTable HT4(N, 4);

    int i = 0;
    int cnt = 0;

    vector<int> ff;
    while(i < N){
        bool g1 = HT1.insert(f[i].first, f[i].second);
        bool g2 = HT2.insert(f[i].first, f[i].second);
        bool g3 = HT3.insert(f[i].first, f[i].second);
        bool g4 = HT4.insert(f[i].first, f[i].second);
        i++;
        if((HT1.loadFactor() >= 0.4 && cnt == 0) || (HT1.loadFactor() >= 0.5 && cnt == 1) || (HT1.loadFactor() >= 0.6 && cnt == 2) || (HT1.loadFactor() >= 0.7 && cnt == 3) || (HT1.loadFactor() >= 0.8 && cnt == 4) || (HT1.loadFactor() >= 0.9 && cnt == 5)){
            if(cnt == 0) {
                cout << "Table 5: Performance of various collision resolution methods in load factor 0.4\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }
            else if(cnt == 1){
                cout << "Table 6: Performance of various collision resolution methods in load factor 0.5\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }
            else if(cnt == 2) {
                cout << "Table 7: Performance of various collision resolution methods in load factor 0.6\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }
            else if(cnt == 3) {
                cout << "Table 8: Performance of various collision resolution methods in load factor 0.7\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }
            else if(cnt == 4) {
                cout << "Table 9: Performance of various collision resolution methods in load factor 0.8\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }
            else if(cnt == 5) {
                cout << "Table 10: Performance of various collision resolution methods in load factor 0.9\n";
                cout << make_str1(" ") <<  make_str2("Before Deletion") << make_str2("After Deletion") << "\n";
                cout << make_str1("method") << make_str1("Avg search time") << make_str1("Avg number of probs") << make_str1("Avg search time") << make_str1("Avg number of probs") << "\n";
            }

            helper1(HT1, 1, i, f);
            helper1(HT2, 2, i, f);
            helper1(HT3, 3, i, f);
            helper1(HT4, 4, i, f);

            cnt++;
        }
        if(HT1.loadFactor() >= 0.9) break;
    }
}

int h1(const string& s, int M){
    int hashValue = 0;
    for(int i=0; i<s.size(); i++){
        hashValue = ((hashValue * 31)%M + s[i] - 'a' + 1)%M;
    }
    return hashValue;
}

int main(){
    int N;
    cin >> N;
    vector<pair<string,int>> f = rand_string(N);

    //freopen("out.txt", "w", stdout);
    cout << N << endl;

    cout << "Table 1: Performance of separate chaining in various load factors\n";
    output_table(N,1,f);
    cout << "Table 2: Performance of linear probing in various load factors\n";
    output_table(N,2,f);
    cout << "Table 3: Performance of quadratic probing in various load factors\n";
    output_table(N,3,f);
    cout << "Table 4: Performance of double hashing in various load factors\n";
    output_table(N,4,f);
    output_table2(N, f);
}
