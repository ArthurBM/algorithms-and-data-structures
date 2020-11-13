#include <bits/stdc++.h>
#include<math.h>
#include <iostream>
#include <queue>
#include<set>
#include<list>
#include<vector>
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
    // void showList(int src, list<Node> lt) {
    //     list<Node> :: iterator i;
    //     Node tempNode;

    //     for(i = lt.begin(); i != lt.end(); i++) {
    //         tempNode = *i;
    //         cout << "(" << src << ")---("<< tempNode.value << "|"<<tempNode.band<<") ";
    //     }
    //     cout << endl;
    // }
public:
    int n;
    list<Node> *adjList;
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

    // void showEdges() {
    //     for (int i = 0; i < n; i++) {
    //         list<Node> tempList = adjList[i];
    //         showList(i, tempList);
    //     }   
    // }

    int getGraphSize() {
        return n;
    }

};

// struct Graph_with_node {
//     int n;
//     Node *adjlist;

//     void setGraphSize(int nodeCount) {
//         n = nodeCount;
//         adjList = new Node[n];
//     }

//     void addEdge(int position, int value, int band) {
//         Node newNode;
//         newNode.value = value;
//         newNode.band = band;
//         adjList[position].push_back(newNode);
//     }
// };


void showpq(priority_queue<int, vector<int>, greater<int> > gq) {
    priority_queue<int, vector<int>, greater<int> > gr = gq;
    while (!gr.empty()) {
        cout << '\t' << gr.top();
        gr.pop();
    }
    cout << '\n';
}

std::pair<vector<int>, vector<int>> djikstra(Graph gr, int origin) {
    vector<int> distances(gr.getGraphSize(), INFINITY);
    vector<int> precursors(gr.getGraphSize(), -1);
    priority_queue<Node, vector<Node>, greater<Node> > min_heap;
    int local_value, local_band, u, d;
    Node *ptr, *e;

    distances[origin] = 0;
    // min_heap.push()
    for (int k = 0; k < gr.getGraphSize() - 1; k++) {
        
        ptr = new Node();
        ptr->value = origin;
        ptr->band = 0;
        min_heap.push(*ptr);
        e = &(gr.adjList[k].front());

        while (e != NULL) {
            local_value = e->value;
            local_band = e->band;
            if ((distances[u] + local_band) < distances[local_value] ) {
                distances[local_value] = distances[u] + local_band;
                //Só falta colocar a parte de heap update aqui
            }
        }

        // for (int i = 0; i < e.size(); i++) {
        //     local_value = e[0].value;
        //     local_band = e[0].band;

        // }
    }

    return std::make_pair(distances, precursors);
    
}


int main(int argc, char *argv[]) {
    // priority_queue <int, vector<int>, greater<int>> gr;
    Graph gr;
    int num_nodes, designated_router;
    int cur_neighbor, cur_weight;
    int num_neighbors;

        while(cin >> num_nodes >> designated_router) {
            gr.setGraphSize(num_nodes);
            for (int adj_list_index = 0; adj_list_index < num_nodes; adj_list_index++) {

                cin >> num_neighbors;

                for (int z = 0; z < (2 * num_neighbors); z++) {
                    if (z % 2 == 0) {
                        cin >> cur_neighbor;
                    }
                    else if (z % 2 != 0) {
                        cin >> cur_weight;
                        gr.addEdge(adj_list_index, cur_neighbor, cur_weight);
                    }
                }
            }

            // gr.showEdges();
            num_nodes = 0; designated_router = 0; cur_neighbor = 0; cur_weight = 0; num_neighbors = 0;
        }
        
    return 0;
}
