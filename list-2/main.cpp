#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
// Primo grande: 291077
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

class User
{
private:
    // Channel channels[291077];
    Stack userHash; //ISSO VAI TER QUE SER UMA LISTA? sim, pois vamos ter que mostrar a lista toda em certo ponto
public:
    // User(string key) {
    //     userHash.push(hash_func(key));
    // }

    int hash_func(string key) {
        int hashValue = 0;

        //Quando você itera por uma string e vai usando cada elemento dela, eles são char, então
        //Se você realiza alguma operação de soma, subtração, etc, o valor usado é o valor da tabela ASCII
        //Por exemplo: '2' vai ser transformado em 50, conforme a tabela
        for( int j = 0; j < key.length(); j++ ) hashValue += key[j];

        int hashKey = hashValue % 291077;
        return hashKey;
    }    
};

class Channel
{
private:
    User users[291077];
public:
    int hash_func(string key) {
        int hashValue = 0;

        for( int j = 0; j < key.length(); j++ ) hashValue += key[j];

        int hashKey = hashValue % 291077;
        return hashKey;
    }

    
};

int main(int argc, char const *argv[])
{
    string s = "455";
    cout << (5 + '2') << endl;
    return 0;
}
