#include<bits/stdc++.h>
#include "LList.cpp"
using namespace std;

class HashNode{
public:
    string key;
    int value;
    HashNode(const string& key, int value){
        this->key = key;
        this->value = value;
    }
    friend bool operator==(const HashNode& a, const HashNode& b);
    friend bool operator!=(const HashNode& a, const HashNode& b);
};

bool operator==(const HashNode& a, const HashNode& b){
    if(a.key == b.key) return true;
    else return false;
}

bool operator!=(const HashNode& a, const HashNode& b){
    if(a.key != b.key) return true;
    else return false;
}

class HashTable{
private:
    LList<HashNode> *list;
    HashNode **arr;
    int type;
    int maxArrSize;
    int curArrSize;
    int listSize;
    int h1(const string& s);
    int h2(const string& s);
public:
    HashNode *D;
    int prob;
    HashTable(int N, int ty);
    ~HashTable();
    bool insert(const string& key, int value);
    bool remove(const string& key);
    HashNode* search(const string& key);
    double loadFactor();
    int getProbe();
    void print();
    int table_size();
    int mx_len();
    void rehash(int v);
};


int HashTable::h1(const string& s){
    int hashValue = 0, M;
    if(type == 1) M = listSize;
    else M = maxArrSize;
    for(int i=0; i<s.size(); i++){
        hashValue = ((hashValue * 31)%M + s[i] - 'a' + 1)%M;
    }
    return hashValue;
}

int HashTable::h2(const string& s){
    int hashValue = 0, M;
    if(type == 1) M = listSize;
    else M = maxArrSize;
    for(int i=0; i<s.size(); i++){
        hashValue = ((hashValue * 37)%M + s[i] - 'a' + 1)%M;
    }
    return hashValue;
}


HashTable::HashTable(int N, int ty){
    this->type = ty;
    if(type == 1){
        listSize = N;
        list = new LList<HashNode> [listSize];
        curArrSize = 0;
        //maxArrSize = N;
    }
    else {
        maxArrSize = N;
        curArrSize = 0;
        arr = new HashNode* [N];
        for(int i=0; i<N; i++) arr[i] = nullptr; 
        D = new HashNode("D",-1);
    }   
}




int HashTable::mx_len(){
    int mx = -1;
    for(int i=0; i<listSize; i++){
        mx = max(mx, list[i].length());
    }
    return mx;
}


bool is_prime(int x){
    for(int i=2; i*i<=x; i++){
        if(x%i == 0) return false; 
    }
    return true;
}


void HashTable::rehash(int v){
    cout << "hi\n";
    int NewSize;
    if(v == 1) NewSize = listSize*1.2;
    else NewSize = listSize*0.8;
    
    while(1){
        //cout << "hello\n";
        if(is_prime(NewSize)){
            int temp = listSize;
            listSize = NewSize;
            LList<HashNode> *NewList = new LList<HashNode> [NewSize];
            for(int i=0; i<temp; i++){
                for(int j=0; j<list[i].length(); j++){
                    list[i].moveToStart();
                    HashNode *F = list[i].getItem();
                    int hash = h1(F->key);
                    NewList[hash].append(F);
                }
            }
            list = NewList;
            break;
        }
        else NewSize++;
        
    }
}







HashTable::~HashTable(){
    if(type == 1) {
        delete list;
    }
    else {
        delete arr;
    }
}

bool HashTable::insert(const string& key, int value){
    HashNode *h = search(key);
    if(h != nullptr) return false;
    HashNode* s = new HashNode(key, value);
    
    int hash = h1(s->key);
    if(type == 1){
        list[hash].append(s);
        curArrSize++;
    }
    else if(type == 2){
        int init = -1;
        
        while(hash != init && arr[hash] != nullptr && *arr[hash] != *D){
            if(init == -1) init = hash;
            hash = (hash + 1)%maxArrSize;
        }

        if(arr[hash] == nullptr){
            arr[hash] = s;
            curArrSize++;
        }
        else if(*arr[hash] == *D){
            arr[hash] = s;
        }
    }
    else if(type == 3){
        int c1=0, c2=1;
        int i=0;
        for(; i<maxArrSize; i++){
            int ind = (hash + c1*i + c2*i*i)%maxArrSize;
            if(arr[ind] == nullptr){
                arr[ind] = s;
                curArrSize++;
                break;
            }
            else if(*arr[ind] == *D){
                arr[ind] = s;
                break;
            }
        }
        if(i == maxArrSize) return false;
    }
    else{
        int hash1 = h2(s->key);
        for(int i=0; i<maxArrSize; i++){
            int ind = (hash + i*hash1)%maxArrSize;
            if(arr[ind] == nullptr){
                arr[ind] = s;
                curArrSize++;
                break;
            }
            else if(*arr[ind] == *D){
                arr[ind] = s;
                break;
            }
        }
    }
    return true;
}


bool HashTable::remove(const string&s){
    HashNode* del = search(s);

    if(del == nullptr) return false;
    int hash = h1(s);
    if(type == 1){
        list[hash].remove(s);
        curArrSize--;
    }
    else {
        *del = *D;
    }
    return true;
}


HashNode* HashTable::search(const string& s){
    prob = 0;
    int hash = h1(s);
    if(type == 1){  
        return list[hash].search(s);
    }
    else if(type == 2){
        int init = -1;
        
        while(hash != init && arr[hash] != nullptr && arr[hash]->key != s){
            if(init == -1) init = hash;
            hash = (hash + 1)%maxArrSize;
            prob++;
        }

        if(arr[hash] != nullptr && arr[hash]->key == s) return arr[hash];
        else  return nullptr;
    }
    else if(type == 3){
        int c1=0, c2=1;

        int ind;
        for(int i=0; i<maxArrSize; i++){
            ind = (hash + c1*i + c2*i*i)%maxArrSize;
            prob++;
            if(arr[ind] == nullptr || arr[ind]->key == s){
                break;
            }
        }

        if(arr[ind] != nullptr && arr[ind]->key == s) return arr[ind];
        else  return nullptr;
    }
    else {
        int hash1 = h2(s);
        int ind;
        for(int i=0; i<maxArrSize; i++){
            ind = (hash + i*hash1)%maxArrSize;
            prob++;
            if(arr[ind] == nullptr || arr[ind]->key == s){
                break;
            }
        }

        if(arr[ind] != nullptr && arr[ind]->key == s) return arr[ind];
        else return nullptr;
    }
}

int HashTable::getProbe(){
    return prob+1;
}

double HashTable::loadFactor(){
    if(type == 1){
        return curArrSize*1.0/listSize;
    }
    else {
        return curArrSize*1.0/maxArrSize;
    }
}

int HashTable::table_size(){
    return curArrSize;
}

void HashTable::print(){
    for(int i=0; i<maxArrSize; i++){
        if(arr[i] == nullptr) cout << "null ";
        else cout << arr[i]->key << " ";
    }
    cout << endl;
}