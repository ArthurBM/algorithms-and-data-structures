//MAX HEAP IMPLEMENTATION WITH THE USE OF DYNAMIC ARRAU IMPLEMENTATION
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

// struct Graph2 {
//     int num_vertices;
//     list<Node> *adjList;
// };

struct Node {
    int value;
    int band;
    int cost = pow(2, 20)/band;
    Node* next;
};

// Create a new node and return a pointer to it
Node* newNode(int value, int band) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->band = band;
    newNode->next = NULL;
    return newNode;
}

int main(int argc, char *argv[]) {
    
    string fstWord = "";

    while (fstWord != "END")
    {
        

    }
    return 0;
}
