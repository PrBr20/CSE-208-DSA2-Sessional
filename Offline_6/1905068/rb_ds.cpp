#include<bits/stdc++.h>

using namespace std;

class Node{
public:
    int key, color, node_count;
    Node *parent, *left, *right;
    Node(int val){
        this->key = val;
        parent = left = right = nullptr;
        color = 0;
        node_count = 1;
    }
};

class RB_Tree{
private :
    Node* root;
    void left_rotate(Node* x);
    void right_rotate(Node* x);
    void rb_insert_fixup(Node* z);
    void rb_delete_fixup(Node* z);
    void rb_transplant(Node* u, Node* v);
    Node* tree_min(Node* x);
    Node* tree_max(Node* x);
    void fixNodeCount1(Node *y);
    int findLessThanX(int val, Node *curr);

public:
    RB_Tree();
    void levelOrder(Node *x);
    void rb_insert(int val);
    void rb_delete(int val);
    Node* rb_find(int val);
    int lessThanX(int val);
    Node* nil;
};

RB_Tree::RB_Tree(){
    nil = new Node(-1);
    nil->color = 1;
    nil->node_count = 0;
    root = nil;
}

int RB_Tree::findLessThanX(int val, Node *curr){
    if(curr == nil) return 0;

    if((curr->key) < val) return (1 + (curr->left)->node_count + findLessThanX(val, curr->right));
    else if((curr->key) == val) return (curr->left)->node_count;
    else return findLessThanX(val, curr->left);
}


int RB_Tree::lessThanX(int val){
    return findLessThanX(val, root);
}

void RB_Tree::fixNodeCount1(Node *x){
    if(x == nil) return;
    else {
        x->node_count = (x->left)->node_count + (x->right)->node_count + 1;
        x = x->parent;
        fixNodeCount1(x);
    }
}

void RB_Tree::left_rotate(Node* x){
    Node *y = x->right;

    int t0 = (x->left)->node_count, t1 = (y->left)->node_count, t2 = (y->right)->node_count;

    x->right = y->left;
    if(y->left != nil) (y->left)->parent = x;
    y->parent = x->parent;
    if(x->parent == nil) root = y;
    else if(x == (x->parent)->left) (x->parent)->left = y;
    else (x->parent)->right = y;
    y->left = x;
    x->parent = y;

    fixNodeCount1(x);
}


void RB_Tree::right_rotate(Node* x){
    Node *y = x->left;

    int t0 = (x->right)->node_count, t1 = (y->right)->node_count, t2 = (y->left)->node_count;

    x->left = y->right;
    if(y->right != nil) (y->right)->parent = x;
    y->parent = x->parent;
    if(x->parent == nil) root = y;
    else if(x == (x->parent)->left) (x->parent)->left = y;
    else (x->parent)->right = y;
    y->right = x;
    x->parent = y;

    fixNodeCount1(x);
}


Node* RB_Tree::tree_max(Node* x){
    Node* y = x;
    while(x != nullptr){
        y = x;
        x = x->right;
    }
    return y;
}


void RB_Tree::rb_insert(int val){
    Node *z = new Node(val);
    Node *x = root, *y = nil;
    while(x != nil){
        y = x;
        if(z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == nil) root = z;
    else if(z->key < y->key) y->left = z;
    else y->right = z;
    z->left = nil;
    z->right = nil;
    z->color = 0;

    fixNodeCount1(z);

    rb_insert_fixup(z);

    //levelOrder(root);
}


void RB_Tree::rb_insert_fixup(Node* z){
    while((z->parent)->color == 0){
        Node *par = z->parent, *gpar = par->parent;
        if(par == gpar->left){
            Node *unc = gpar->right;
            if(unc->color == 0){
                par->color = 1;
                unc->color = 1;
                gpar->color = 0;
                z = gpar;
            }
            else {
                if(z == par->right){
                    z = z->parent;
                    left_rotate(z);
                }
                (z->parent)->color = 1;
                ((z->parent)->parent)->color = 0;
                right_rotate((z->parent)->parent);
            }
        }
        else {
            Node *unc = gpar->left;
            if(unc->color == 0){
                par->color = 1;
                unc->color = 1;
                gpar->color = 0;
                z = gpar;
            }
            else {
                if(z == par->left){
                    z = z->parent;
                    right_rotate(z);
                }
                (z->parent)->color = 1;
                ((z->parent)->parent)->color = 0;
                left_rotate((z->parent)->parent);
            }
        }
    }
    root->color = 1;
}

Node* RB_Tree::rb_find(int val){
    Node *x = root;
    while(x != nil){
        if(val > x->key) x = x->right;
        else if(val < x->key) x = x->left;
        else return x;
    }
    return x;
}

Node* RB_Tree::tree_min(Node* x){
    Node *y = x;
    while(x != nil){
        y = x;
        x = x->left;
    }
    return y;
}

void RB_Tree::rb_transplant(Node* u, Node* v){
    if(u->parent == nil) root = v;
    else if(u == (u->parent)->left) (u->parent)->left = v;
    else (u->parent)->right = v;
    v->parent = u->parent;
}

void RB_Tree::rb_delete(int val){
    Node *z = rb_find(val), *y = z, *x = nil;
    int col_y = y->color;
    if(z->left == nil){
        Node *g = z->parent;
        x = z->right;
        rb_transplant(z, z->right);
        fixNodeCount1(g);
    }
    else if(z->right == nil){
        Node *g = z->parent;
        x = z->left;
        rb_transplant(z,z->left);
        fixNodeCount1(g);
    }
    else {
        y = tree_min(z->right);
        Node *g = y->parent;
        col_y = y->color;
        x = y->right;

        if(y->parent == z){
            x->parent = y;
        }
        else {
            rb_transplant(y, y->right);
            y->right = z->right;
            (y->right)->parent = y;
        }
        rb_transplant(z,y);
        y->left = z->left;
        (y->left)->parent = y;
        y->color = z->color;
        fixNodeCount1(g);
    }

    if(col_y == 1){
        rb_delete_fixup(x);
    }

    //levelOrder(root);
}


void RB_Tree::rb_delete_fixup(Node *x){
    while(x != root && x->color == 1){
        if(x == (x->parent)->left){
            Node *w = (x->parent)->right;
            if(w->color == 0){
                w->color = 1;
                (x->parent)->color = 0;
                left_rotate(x->parent);
                w = (x->parent)->right;
            }
            if((w->left)->color == 1 && (w->right)->color == 1){
                w->color = 0;
                x = x->parent;
            }
            else {
                if((w->right)->color == 1){
                    (w->left)->color = 1;
                    w->color = 0;
                    right_rotate(w);
                    w = (x->parent)->right;
                }
                w->color = (x->parent)->color;
                (x->parent)->color = 1;
                (w->right)->color = 1;
                left_rotate(x->parent);
                x = root;
            }
        }
        else {
            Node *w = (x->parent)->left;
            if(w->color == 0){
                w->color = 1;
                (x->parent)->color = 0;
                right_rotate(x->parent);
                w = (x->parent)->left;
            }
            else {
                if((w->left)->color == 1 && (w->right)->color == 1){
                    w->color = 0;
                    x = x->parent;
                }
                else {
                    if((w->left)->color == 1){
                        (w->right)->color = 1;
                        w->color = 0;
                        left_rotate(w);
                        w = (x->parent)->left;
                    }
                    w->color = (x->parent)->color;
                    (x->parent)->color = 1;
                    (w->left)->color = 1;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
    }
    x->color = 1;
}

void RB_Tree::levelOrder(Node *x) {
    if (x == nil) return;

    queue<Node *> q;
    Node *curr;

    q.push(x);

    while (!q.empty()) {
      curr = q.front();
      q.pop();

      cout << curr->key << " " << curr->color << " " << curr->node_count << " ";
      if(curr->parent != nil) cout << (curr->parent)->key << endl;
      else cout << endl;

      if (curr->left != nil)
        q.push(curr->left);
      if (curr->right != nil)
        q.push(curr->right);
    }
}
