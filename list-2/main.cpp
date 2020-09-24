#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
// Primo grande: 9343
struct Node
{
    string id;
    int score;
    Node *link;
};

class Queue
{
private:
    Node *rear = NULL;
    Node *front = NULL;
    int queueSize = 0;
    int beforeScore;

public:
    bool isEmpty()
    {
        return (rear == NULL && front == NULL) ? true : false;
    }

    //Adiciona ao final
    void enqueue(string id, int score)
    {
        Node *ptr = new Node();
        ptr->id = id;
        ptr->score = score;
        ptr->link = NULL;
        if (queueSize == 0)
        {
            front = ptr;
            rear = ptr;
        }
        else
        {
            rear->link = ptr;
            rear = ptr;
        }
        // cout << score << endl;
        queueSize += 1;
        cout << "queue size:" << queueSize << endl;
    }

    //Retira do início
    void dequeue()
    {
        if (isEmpty()) cout << "NULL" << endl;
        
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
            queueSize -= 1;
        }
    }

    void showStart()
    {
        if (isEmpty()) return;
        
        else cout << front->id << endl;
        
    }

    int getSize()
    {
        return queueSize;
    }

    Node* getFront() {
        return front;
    }

    int lastScore() {
        return rear->score;
    }

    void makeSubscription(string id, int score) {
        bool foundId = false;
        if (isEmpty()) {
            enqueue(id, score);
            return;
        }
        else {
            Node *ptr = front;
            do 
            {
                if(ptr->id == id) {
                    ptr->score = score;
                    foundId = true;
                    // free(ptr);
                    return;
                }
                else ptr = ptr->link;
            }while (ptr->link != NULL);
            // free(ptr);
            if (!foundId) {
                enqueue(id,score);
            }
            // return false;
        }
    }
};

//Isso vai ficar feioso pois você ia ter que colocar o id do user e do channel
void makeSubscription(string id, int score, Queue& userQueue, Queue &channelQueue) {
        bool foundId = false;
        if (userQueue.isEmpty()) {
            userQueue.enqueue(id, score);
        }
        else {
            Node *ptr = userQueue.getFront();
            while (ptr->link != NULL)
            {
                if(ptr->id == id) {
                    ptr->score = score;
                    foundId = true;
                    // free(ptr);

                }
                else 
                    ptr = ptr->link;
            }
            // free(ptr);
            if (!foundId) {
                userQueue.enqueue(id,score);
            }
            // return false;
        }
        if (channelQueue.isEmpty()) {
            channelQueue.enqueue(id, score);
            cout << score << endl;
        }
        else {
            Node *ptr = channelQueue.getFront();
            while (ptr->link != NULL)
            {
                if(ptr->id == id) {
                    cout << score << endl;
                    ptr->score = score;
                    foundId = true;
                    // free(ptr);

                }
                else 
                    ptr = ptr->link;
            }
            // free(ptr);
            if (!foundId) {
                channelQueue.enqueue(id,score);
                cout << score << endl;
            }
            // return false;
        }
    }

int hash_func(string key) {
    int hashValue = 0;

    //Quando você itera por uma string e vai usando cada elemento dela, eles são char, então
    //Se você realiza alguma operação de soma, subtração, etc, o valor usado é o valor da tabela ASCII
    //Por exemplo: '2' vai ser transformado em 50, conforme a tabela
    for(int j = 0; j < key.length(); j++ ) hashValue += key[j];

    int hashKey = hashValue % 9343;
    return hashKey;
}



// void new_subscription(string userId, string channelId, int score) {
//     //Adiciona um id de user e um score a uma posição do hash de channels    
    
//     //Adiciona um id de channel e um score a uma posição do hash de users
// }


int main(int argc, char const *argv[])
{
    Queue users[9343], channels[9343];
    string fstWord="", userId="", channelId="";
    int score;

    while (fstWord != "END")
    {
        cin >> fstWord;

        if(fstWord == "SUB") {
            cin >> userId;
            cin >> channelId;
            cin >> score;
            
            users[hash_func(userId)].makeSubscription(channelId, score);
            channels[hash_func(channelId)].makeSubscription(userId, score);

            cout << channels[hash_func(channelId)].lastScore() << endl;

        }
        //Terei que criar uma função para percorrer o array 
        else if(fstWord == "CHN") {
            cin >> userId;
            
        }
        //Terei que guardar o valor 
        else if(fstWord == "USR") {
            cin >> channelId;
            
        }
        else if(fstWord == "SCO") {
            cin >> userId;
            cin >> channelId;
        }
        else if(fstWord == "RMU") {
            cin >> userId;
        }

        userId = "";
        channelId = "";
    }
    
    return 0;
}
