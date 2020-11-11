//MAX HEAP IMPLEMENTATION WITH THE USE OF DYNAMIC ARRAU IMPLEMENTATION
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include<set>
#include<list>
#define endl '\n'

using namespace std;

struct Node {
    int value;
    int band;
    int cost = pow(2, 20)/band;
    Node* next;
};

class Graph {
private:
    int n;
    list<Node> *adjList;
    void showList(int src, list<Node> lt) {
        list<Node> :: iterator i;
        Node tempNode;

        for(i = lt.begin(); i != lt.end(); i++) {
            tempNode = *i;
            cout << "(" << src << ")---("<< tempNode.value << "|"<<tempNode.band<<") ";
        }
        cout << endl;
    }
public:
    Graph() {
        n=0;
    }

    Graph(int nodeCount) {
        n = nodeCount;
        adjList = new list<Node>[n];
    }

    void setGraphSize(int nodeCount) {
        n = nodeCount;
        adjList = new list<Node>[n];
    }

    void addEdge(int position, int value, int band) {
        Node newNode;
        newNode.value = value;
        newNode.band = band;
        adjList[position].push_back(newNode);
    }

    void showEdges() {
        for (int i = 0; i < n; i++) {
            list<Node> tempList = adjList[i];
            showList(i, tempList);
        }   
    }

};


void showpq(priority_queue<int, vector<int>, greater<int> > gq) {
    priority_queue<int, vector<int>, greater<int> > g = gq;
    while (!g.empty()) {
        cout << '\t' << g.top();
        g.pop();
    }
    cout << '\n';
}

// std::pair<int[], int[]> djikstra() {

// }


int main(int argc, char *argv[]) {
    // priority_queue <int, vector<int>, greater<int>> g;
    Graph g(3);
    int num_nodes, designated_router;

    

    return 0;
}
