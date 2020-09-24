#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
// Primo grande: 291077
struct Node
{
    string id, score;
    int index;
    Node *link;
};

class List
{
private:
    Node sentinel;
    Node *head = &sentinel;
public:
    //COMO TRATAR O CASO DE A POSIÇÃO NÃO ESTAR NA LISTA?
    //Retorna um ponteiro para o nó da posição desejada
    Node* pos(int position) {
        Node *cur = head;
        int i =0;
        while ((i < position) && (cur->link != NULL))
        {
            cur = (cur->link);
            i++;
        }

        return cur;
    }
    //COMO TRATAR O CASO DE O ELEMENTO NÃO ESTAR NA LISTA?
    //Retorna um ponteiro para o primeiro nó que contém o valor desejado
    Node* find(string value) {
        Node *cur = head;
        while ((cur->link != NULL) && ((cur->link)->id != value))
        {
            cur = (cur->link);
        }
        return cur;
    }

    void list_insert(Node* cursor, string value, string score) {
        Node *ptr = new Node();
        ptr->id = value;
        ptr->score = score;
        if (cursor->link != NULL) ptr->link = cursor->link;
        else ptr->link = NULL;
        cursor->link = ptr;
    }

    Node* list_insert_return(Node* cursor, string value, string score) {
        Node *ptr = new Node();
        ptr->id = value;
        ptr->score = score;
        if (cursor->link != NULL) ptr->link = cursor->link;
        else ptr->link = NULL;
        cursor->link = ptr;
        return cursor;
    }

    //NESSE CASO VOCÊ NÃO VAI PODER DELETAR O ÚLTIMO ELEMENTO
    void list_delete(Node* cursor) {
        Node *ptr = cursor->link;
        cursor->link = ptr->link;
        string value = ptr->id;
        free(ptr);
    }
    
};

class Stack2 : public List
{
private:
    Node sentinel;
    Node *top = &sentinel;
public:
    Stack2() {
        top->link = NULL;
    }
    bool isEmpty() {
        return (top->link == NULL) ? true : false;
    }
    void push(string value, string score) {
        list_insert(top, value, score);
    }

    void pop() {
        if (isEmpty()) {
            cout << "NULL" << endl;
        }

        else list_delete(top);
    }

    string showTop() {
        return (top->link)->id;
    }
};

class Queue : public List
{
private:
    Node sentinel;
    Node *head = &sentinel, *tail = &sentinel;
public:
    void enqueue(string value, string score) {
        tail = list_insert_return(tail, value, score);
        

    }
};


int main(int argc, char const *argv[])
{
    Stack2 s;
    // s.push("2");
    s.pop();
    

    // cout << s.showTop() << endl;
    return 0;
}
