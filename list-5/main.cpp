#include <bits/stdc++.h>
#include<math.h>
#include <iostream>
#include <queue>
#include<set>
#include<list>
#include<vector>
#define endl '\n'

using namespace std;

typedef pair<int, int> iPair; 

struct Node {
    int value;
    int band;
    int cost = pow(2, 20)/band;
};

class Graph {
private:

public:
    int N;
    list<Node> *adjList;

    void setGraphSize(int nodeCount) {
        N = nodeCount;
        adjList = new list<Node>[N];
    }

    void addEdge(int position, int value, int band) {
        Node newNode;
        newNode.value = value;
        newNode.band = band;
        adjList[position].push_back(newNode);
    }

    int getGraphSize() {
        return N;
    }

    std::pair<vector<int>, vector<int> > dijkstra(int origin) {
        vector<int> dist(N, INFINITY);
        vector<int> prec(N, INFINITY);
        priority_queue<Node, vector<Node>, greater<Node> > pq;

        //Elo (v, d[v])
        Node* ptr = new Node();
        ptr->value = origin;
        ptr->band = 0;

        pq.push(*ptr);
        dist[origin] = 0;
        
        while (!pq.empty()) {
            //Aqui talvez seja cost
            int u = pq.top().value;
            pq.pop();

            // 'i' is used to get all adjacent vertices of a vertex 
            list<Node>::iterator i;
            for (i = adjList[u].begin(); i != adjList[u].end(); ++i) {
                int value = (*i).value;
                int cost = (*i).cost;

                if (dist[u] + cost < dist[value]) {
                    dist[value] = dist[u] + cost;
                    prec[value] = u;
                    //Falta o heap update aqui
                    Node* ptr2 = new Node();
                    ptr2->value = dist[value];
                    ptr2->band = pow(2, 20)/value;
                    pq.push(*ptr2);
                }

            }
        }

        return (make_pair(dist, prec));

    }

};


void showpq(priority_queue<int, vector<int>, greater<int> > gq) {
    priority_queue<int, vector<int>, greater<int> > gr = gq;
    while (!gr.empty()) {
        cout << '\t' << gr.top();
        gr.pop();
    }
    cout << '\n';
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
