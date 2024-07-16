#include<bits/stdc++.h>

using namespace std;

struct FibHeapNode
{
    int key;
    FibHeapNode* left;
    FibHeapNode* right;
    FibHeapNode* child;
    FibHeapNode* parent;
    int degree;
    bool mark;
    int id;
};

class FibHeap{
private :
    static const int minimumKey = -INT_MAX;

    void _remove_from_circular_list(FibHeapNode* x);
    FibHeapNode* _union(FibHeapNode* a, FibHeapNode* b);
    void _consolidate();
    FibHeapNode* _extract_min_node();
    void _cut(FibHeapNode* x, FibHeapNode* y);
    void _cascading_cut(FibHeapNode* y);
    void _clear(FibHeapNode* x);

public:
    FibHeapNode* minNode;
    int numOfNodes;

    FibHeap(){
        minNode = nullptr;
        numOfNodes = 0;
    }

    ~FibHeap(){
        _clear(minNode);
    }

    FibHeapNode* insert(int newKey){
        FibHeapNode* x = new FibHeapNode;
        x->key = newKey;
        x->left = x;
        x->right = x;
        x->child = nullptr;
        x->parent = nullptr;
        x->degree = 0;
        x->mark = false;

        minNode = _union(minNode, x);
        numOfNodes++;
        
        return x;
    }

    void unionTwo(FibHeap& another){
        _union(minNode, another.minNode);
        numOfNodes += another.numOfNodes;
        another.minNode = nullptr;
        another.numOfNodes = 0;
    }   

    int extract_min(){
        FibHeapNode* mini = _extract_min_node();
        int d = mini->id;
        
        delete mini;
        numOfNodes--;
        return d;
    };

    void decrease_key(FibHeapNode* x, int newKey){
        x->key = newKey;
        FibHeapNode* y = x->parent;
        if(y != nullptr && x->key < y->key){
            _cut(x,y);
            _cascading_cut(y);
        }
        if(x->key < minNode->key){
            minNode = x;
        }
    }

    void delete_node(FibHeapNode* x){
        decrease_key(x, minimumKey);
        _extract_min_node();
    };

};


FibHeapNode* FibHeap::_union(FibHeapNode* a, FibHeapNode* b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;

    if(a->key > b->key){
        swap(a,b);
    }

    FibHeapNode* ar = a->right;
    FibHeapNode* bl = b->left;
    a->right = b;
    b->left = a;
    ar->left = bl;
    bl->right = ar;    
    return a;
}



void FibHeap::_remove_from_circular_list(FibHeapNode* x){
    if(x->right == x) return;

    (x->left)->right = x->right;
    (x->right)->left = x->left;
    x->left = x->right = x;
}

FibHeapNode* FibHeap::_extract_min_node(){
    FibHeapNode* mn = minNode;
    if (mn == nullptr){
        return nullptr;
    }

    FibHeapNode* z = mn->child;
    if(z != nullptr){
        do{
            z->parent = nullptr;
            z = z->right;
        }while(z != mn->child);
    }

    _union(mn, mn->child);
    if (mn == mn->right){
        minNode = nullptr;
    }else{
        minNode = mn->right;
    }
    _remove_from_circular_list(mn);
    if (minNode != nullptr){
        _consolidate();
    }
    return mn;
}

void FibHeap::_consolidate(){
    int Dn = (log2(numOfNodes) / log2(1.618));
    FibHeapNode** dg = new FibHeapNode*[Dn+1];
  
    for(int i=0; i<Dn+1; i++) dg[i] = nullptr;
    vector<FibHeapNode*> nodelist;
    FibHeapNode* curr = minNode;
    do{
        nodelist.push_back(curr);
        curr = curr->right;
    }while(curr != minNode);

    for(auto e: nodelist){
        int de = e->degree;
        _remove_from_circular_list(e);
        while(dg[de] != nullptr){
            auto tmp = dg[de];
            if(e->key > tmp->key){
                swap(e,tmp);
            }

            tmp->parent = e;
            tmp->mark = false;
            e->child = tmp;
            e->degree++;
            
            dg[de] = nullptr;
            de++;
        }
        dg[e->degree] = e;
        minNode = e; 
    }

    for(int i=0; i<Dn+1; i++){
        if(dg[i]!= nullptr && dg[i] != minNode){
            _union(minNode, dg[i]);
        }
    }

    FibHeapNode* mn = minNode;
    FibHeapNode* iter = mn;
    do{
        if(iter->key < minNode->key){
            minNode = iter;
        }
        iter = iter->right;
    }while(iter != mn);
    delete[]dg;
}

void FibHeap::_cut(FibHeapNode* x, FibHeapNode* y){
    if(x == x->right){
        y->child = nullptr;
    }
    else y->child = x->right;

    _remove_from_circular_list(x);
    _union(minNode, x);
    x->parent = nullptr;
    x->mark = false;
    y->degree--; 
}

void FibHeap::_cascading_cut(FibHeapNode* x){
    FibHeapNode* z = x->parent;
    while(z != nullptr){
        if(x->mark == false){
            x->mark = true;
        }
        else {
            _cut(x,z);
            _cascading_cut(z);
        }
    }
}


void FibHeap::_clear(FibHeapNode* x){
    if(x != nullptr){
        FibHeapNode* t1 = x;
        do {
            FibHeapNode* t2 = t1;
            t1 = t1->right;
            _clear(t2->child);
            delete t2;
        }while(t1 != x);
    }
}