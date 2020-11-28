//MAX HEAP IMPLEMENTATION WITH THE USE OF DYNAMIC ARRAU IMPLEMENTATION
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef pair<int, int> iPair; 

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

class Graph {
private:
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

    void showEdges() {
        for (int i = 0; i < n; i++) {
            list<Node> tempList = adjList[i];
            showList(i, tempList);
        }   
    }

    int getGraphSize() {
        return n;
    }

};

std::pair<vector<int>, vector<int>> djikstra(Graph gr, int origin) {
    vector<int> distances(gr.getGraphSize(), INFINITY);
    vector<int> precursors(gr.getGraphSize(), -1);
    list<Node> e;
    priority_queue<Node, vector<Node>, greater<Node> > min_heap;
    int local_value, local_band, u, d;
    Node nd, *e2;

    distances[origin] = 0;
    // min_heap.push()
    for (int k = 0; k < gr.getGraphSize() - 1; k++) {
        nd.value = origin;
        nd.band = 0;
        min_heap.push(nd);
        e = gr.adjList[k];
        e2 = &(e.front());
        
        

        // for (int i = 0; i < e.size(); i++) {
        //     local_value = e[0].value;
        //     local_band = e[0].band;

        // }
    }

    return std::make_pair(distances, precursors);
    
}

class Graph2 {
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
    Graph2() {
        n=0;
    }

    Graph2(int nodeCount) {
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

std::pair<vector<int>, vector<int> > djikstra(Graph2 gr, int origin) {
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

        //Percorrendo todos os vizinhos de 
        while (e != NULL) {
            local_value = e->value;
            local_band = e->band;
            if ((distances[u] + local_band) < distances[local_value] ) {
                distances[local_value] = distances[u] + local_band;
                //Só falta colocar a parte de heap update aqui
            }
            //Em vez de fazer e = e->next você fará (Usando iterator? Melhor não. Transforme o grafo num vector com)
        }

        // for (int i = 0; i < e.size(); i++) {
        //     local_value = e[0].value;
        //     local_band = e[0].band;

        // }
    }

    return std::make_pair(distances, precursors);
    
}

class Graph3 {
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
        priority_queue< iPair, vector<iPair>, greater<iPair> > pq;

        //Elo (v, d[v])
        // Node* ptr = new Node();
        // ptr->value = origin;
        // ptr->band = 0;

        pq.push(make_pair(0, origin));
        dist[origin] = 0;
        
        while (!pq.empty()) {
            //Aqui talvez seja cost
            int u = pq.top().second;
            pq.pop();

            // 'i' is used to get all adjacent vertices of a vertex 
            list< Node >::iterator i;
            for (i = adjList[u].begin(); i != adjList[u].end(); ++i) {
                int value = i->value;
                int band = i->band;
                int cost = i->cost;

                if (dist[u] + (pow(2,20)/band) < dist[value]) {
                    dist[value] = dist[u] + (pow(2,20)/band);
                    prec[value] = u;
                    // //Falta o heap update aqui (Será que vai precisar?)
                    // Node* ptr2 = new Node();
                    // ptr2->value = dist[value];
                    // ptr2->band = pow(2, 20)/value;
                    pq.push(make_pair(dist[value], value));
                }

            }
        }

        return (make_pair(dist, prec));
    }

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
