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
    Graph g;
    int num_nodes, designated_router;
    int cur_neighbor, cur_weight;
    int num_neighbors;
    
        cin >> num_nodes;
        cin >> designated_router;
        g.setGraphSize(num_nodes);

        do {

            for (int adj_list_index = 0; adj_list_index < num_nodes; adj_list_index++) {

                cin >> num_neighbors;

                for (int z = 0; z < (2 * num_neighbors); z++) {
                    if (z % 2 == 0) {
                        cin >> cur_neighbor;
                    }
                    else if (z % 2 != 0) {
                        cin >> cur_weight;
                        g.addEdge(adj_list_index, cur_neighbor, cur_weight);
                    }
                }
            }

            g.showEdges();
            num_nodes = 0; designated_router = 0; cur_neighbor = 0; cur_weight = 0; num_neighbors = 0;
            
        } while(cin.get() != '\n');
        
    
    return 0;
}
