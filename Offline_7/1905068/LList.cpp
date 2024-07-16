#include<bits/stdc++.h>
#include"List_interface.h"
using namespace std;

template<typename E> class Link
{
public :
    E* element;
    Link<E>* next;

    Link(E* it, Link<E>* nextval)
    {
        element = it;
        next = nextval;
    }
    Link(){

    }
    Link<E> getNext()
    {
        return next;
    }
    Link<E> setNext(Link<E> nextval)
    {
        return next = nextval;
    }
    E getElement()
    {
        return element;
    }
    void setElement(E it)
    {
        element = it;
    }
};


template <typename E> class LList: public List<E>
{
private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;
    void init()
    {
        curr = tail = head = new Link<E>;
        cnt = 0;
        curr->next = NULL;
    }
    void removeall()
    {
        while(head != NULL)
        {
            curr = head;
            head = head->next;
            delete curr;
        }
        curr->next = NULL;
    }
public:
    LList(int size, E a[]){
        init();
        cnt = size;
        curr->next = new Link<E>;
        Link<E>* temp = curr->next;
        for(int i=0; i<size-1; i++){
            temp->element = a[i];
            temp->next = new Link<E>(a[i+1] , NULL);
            temp = temp->next;
        }
        tail = temp;
    }
    LList(){
        init();
    }
    ~LList(){
        removeall();
    }
    void clear()
    {
        removeall();
        init();
    }
    void insert(E* it)
    {
        curr->next = new Link<E>(it, curr->next);
        if (tail == curr) tail = curr->next;
        cnt++;
    }
    void append(E* it)
    {
        tail = tail->next = new Link<E>(it, NULL);
        cnt++;
        //print(this);
    }

    void remove(const string& item)
    {
        int pos = -1, num = -1;
        Link<E>* temp = head;
        curr = head;

        while(temp != nullptr)
        {
            if(temp != head && (temp->element)->key == item){
                break;
            }
            curr = temp;
            temp = temp->next;
            num++;
        }
        
        Link<E>* ltemp = curr->next;
        if (tail == curr->next) {
            tail = curr;
            curr->next = NULL;
        }
        else curr->next = (curr->next)->next;
        delete ltemp;
        cnt--;
        
    }
    void moveToStart()
    {
        curr = head;
    }
    void moveToEnd()
    {
        while(curr->next != tail) curr = curr->next;
    }
    void prev()
    {
        if (curr == head) return;
        Link<E>* temp = head;
        while (temp->next!=curr) temp=temp->next;
        curr = temp;
    }
    void next()
    {
        if (curr != tail) curr = curr->next;
    }
    int length()
    {
        return cnt;
    }
    int currPos()
    {
        Link<E>* temp = head;
        int i;
        for (i=0; curr != temp; i++)
            temp = temp->next;
        return i;
    }
    void moveToPos(int pos)
    {
        curr = head;
        for(int i=0; i<pos; i++) curr = curr->next;
    }
    string getValue()
    {
        return curr->next->element->key;
    }
    E* search(const string& item){
        int pos = -1, num = -1;
        Link<E>* temp = head;
        E* val = nullptr;

        while(temp != nullptr)
        {
            if(temp != head && (temp->element)->key == item){
                val = temp->element;
                break;
                pos = num;
            }
            temp = temp->next;
            num++;
        }
        return val;
    }
    int search_pos(const string& item){
        int pos = -1, num = -1;
        Link<E>* temp = head;

        while(temp != nullptr)
        {
            if(temp != head && (temp->element)->key == item){
                pos = num;
            }
            temp = temp->next;
            num++;
        }
        //cout << num << endl;
        return num;
    }
    E* getItem(){
        return curr->next->element;
    }
};

template<typename E> void print(LList<E>* l){
    
    int curr = l->currPos();
    l->moveToStart();
    cout << "<";
    while(l->currPos() != l->length()){
        if(curr == l->currPos()) cout << "| ";
        cout << l->getValue();
        if(l->currPos() != l->length() - 1) cout << " ";
        l->next();
    }
    cout << ">" << endl;
    l->moveToPos(curr);
}

