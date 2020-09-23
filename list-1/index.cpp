#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Node
{
    string data;
    int index;
    Node *link;
};

class Stack
{
private:
    Node *top = NULL;
    int topIndex = 0;

public:
    bool isEmpty()
    {
        return (top == NULL) ? true : false;
    }

    void push(string value)
    {
        topIndex += 1;
        Node *ptr = new Node();
        ptr->data = value;
        ptr->link = top;
        ptr->index = topIndex;
        top = ptr;
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }
        else
        {
            Node *ptr = top;
            //Era top aí em ptr, mas deixei pra ver se funciona
            top = top->link;
            topIndex -= 1;
            delete (ptr);
        }
    }

    string getTop()
    {
        if (isEmpty())
        {
            return "NULL";
        }
        else
        {
            return top->data;
        }
    }

    void showTop()
    {
        if (isEmpty())
        {
            cout << "NULL" << endl;
        }
        else
        {
            cout << top->data << endl;
        }
    }

    void showIndexTop()
    {
        if (isEmpty())
        {
            cout << 0 << endl;
        }
        else
        {
            cout << top->index << endl;
        }
    }

    void deleteAll()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

class Queue
{
private:
    Node *rear = NULL;
    Node *front = NULL;
    int numPages = 0;

public:
    bool isEmpty()
    {
        return (rear == NULL && front == NULL) ? true : false;
    }

    //Adiciona ao final
    void enqueue(string value)
    {
        Node *ptr = new Node();
        ptr->data = value;
        ptr->link = NULL;
        if (numPages == 0)
        {
            front = ptr;
            rear = ptr;
        }
        else
        {
            rear->link = ptr;
            rear = ptr;
        }
        numPages += 1;
    }

    //Retira do início
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "NULL" << endl;
        }
        else
        {
            //Caso só tenha um elemento
            if (front == rear)
            {
                /*Estou liberando o lugar que front aponta, mas front e rear ainda existem, quando você usa a função "delete"
                você está deletando o ponteiro e o lugar para onde ele está apontando*/
                free(front);
                front = NULL;
                rear = NULL;
            }

            else
            {
                Node *ptr = front;
                front = front->link;
                free(ptr);
            }
            numPages -= 1;
        }
    }

    void showStart()
    {
        if (isEmpty())
        {
            return;
        }
        else
        {
            cout << front->data << endl;
        }
    }

    int getNumPages()
    {
        return numPages;
    }
};

int main(int argc, char *argv[])
{
    Stack sites;
    Queue savedSites;

    string fstWord, scndWord;

    while (fstWord != "END")
    {
        cin >> fstWord;

        if (fstWord == "OPN")
        {
            cin >> scndWord;
        }
        
        if (fstWord == "OPN")
        {
            sites.push(scndWord);
            sites.showIndexTop();
        }

        else if (fstWord == "CUR")
        {
            sites.showTop();
        }

        else if (fstWord == "BCK")
        {
            sites.pop();
            sites.showTop();
        }

        else if (fstWord == "PAN")
        {
            sites.showIndexTop();
            sites.deleteAll();
        }

        else if (fstWord == "SAV")
        {
            if (sites.getTop() != "NULL")
            {
                savedSites.enqueue(sites.getTop());
            }
            cout << savedSites.getNumPages() << endl;
        }

        else if (fstWord == "REA")
        {
            savedSites.showStart();
            savedSites.dequeue();
        }
        // cout << fstWord << endl;
    }

    return 0;
}
