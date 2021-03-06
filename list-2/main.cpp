#include <bits/stdc++.h>
// #include <string>
#define endl '\n'

using namespace std;
// Primo grande: 151
struct Node
{
    string id;
    int score;
    Node *link;
};

class Queue
{
protected:
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
        // cout << "queue size:" << queueSize << endl;
    }

    //Retira do início
    void dequeue()
    {
        if (isEmpty()) return;
        
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

    int getQueueSize()
    {
        return queueSize;
    }

    Node* getFront() {
        return front;
    }

    int lastScore() {
        return rear->score;
    }

    void makeSubscription(string id, int score, bool shouldPrint) {
        bool foundId = false;
        if (isEmpty()) {
            enqueue(id, score);
            if (shouldPrint) 
                cout << score << endl;
        }
        else {
            Node *ptr = front;
            do 
            {
                if(ptr->id == id) {
                        
                    if (shouldPrint) {
                        cout << ptr->score << endl;
                    }

                    ptr->score = score;
                    foundId = true;
                    break;
                }
                else //if (ptr->link != NULL)
                    ptr = ptr->link;
            } while (ptr!= NULL);
            //Dessa forma o último valor assumido por ptr será o último elemento,
            //Você poderia fazer colocando dentro do while só ptr != NULL e o último else if ser só um else
            if (!foundId) {
                enqueue(id,score);
                if (shouldPrint) 
                    cout << score << endl;
            }
        }
    }

};

class UserQueue : public Queue
{
private:
    /* data */
public:
    void listChannels() {
        if (isEmpty())
            cout << "0" << endl;
        else {
            Node *ptr = front;
            do
            {
                cout << ptr->id << " ";
                ptr = ptr->link;
            } while (ptr != NULL);
            cout << endl;
        }
    }

    void scoreChannel(string channelId) {
        bool foundChannel = false;
        if (isEmpty()) {
            cout << "0" << endl;
        }

        else {
            Node *ptr = front;
            do
            {
                if(ptr->id == channelId) {
                    foundChannel = true;
                    cout << ptr->score << endl;
                    break;
                }
                else
                    ptr = ptr->link;
            } while (ptr != NULL);

            if (!foundChannel)
                cout << "0" << endl;
            
        }
    }

    void deleteAllElements() {
        while (!isEmpty()) {
            cout << queueSize << endl;
            dequeue();
        }
    }
};

class ChannelQueue : public Queue
{
private:
    /* data */
public:
    void deleteUser(string userId) {
        if (isEmpty()) {
            return;
        }
        if (queueSize == 1) {
            dequeue();
            return;
        }
        else {
            Node *cursor = front;
            Node *previousCursor = front;
            do
            {
                //Isso está deletando um nó e consertando a configuração da fila
                //Como se fosse um list-delete
                if ((cursor->link)->id == userId) {
                    Node *ptr = cursor->link;
                    cursor->link = ptr->link;
                    free(ptr);
                    queueSize-=1;
                }
                else
                    cursor = cursor->link;
            } while (cursor != NULL);
            
        }
    }
};

int hash_func(string key) {
    int hashValue = 0;

    //Quando você itera por uma string e vai usando cada elemento dela, eles são char, então
    //Se você realiza alguma operação de soma, subtração, etc, o valor usado é o valor da tabela ASCII
    //Por exemplo: '2' vai ser transformado em 50, conforme a tabela
    for(int j = 0; j < key.length(); j++ ) hashValue += key[j];

    int hashKey = hashValue % 151;
    return hashKey;
}

int main(int argc, char const *argv[])
{
    ChannelQueue channels[151];
    UserQueue users[151];
    string fstWord="", userId="", channelId="";
    int score;

    while (fstWord != "END")
    {
        cin >> fstWord;

        if(fstWord == "SUB") {
            cin >> userId;
            cin >> channelId;
            cin >> score;
            
            users[hash_func(userId)].makeSubscription(channelId, score, true);
            channels[hash_func(channelId)].makeSubscription(userId, score, false);

            // cout << channels[hash_func(channelId)].lastScore() << endl;
        }
        //Terei que criar uma função para percorrer o array 
        else if(fstWord == "CHN") {
            cin >> userId;
            users[hash_func(userId)].listChannels();
            
        }
        //Terei que guardar o valor 
        else if(fstWord == "USR") {
            cin >> channelId;

            cout << channels[hash_func(channelId)].getQueueSize() << endl;
            
        }
        else if(fstWord == "SCO") {
            cin >> userId;
            cin >> channelId;

            users[hash_func(userId)].scoreChannel(channelId);
        }
        else if(fstWord == "RMU") {
            cin >> userId;

            users[hash_func(userId)].deleteAllElements();

            for (int i = 0; i < 151; i++) {
                string key = to_string(i);
                channels[hash_func(key)].deleteUser(userId);
            }
        }

        userId = "";
        channelId = "";
    }
    
    return 0;
}
