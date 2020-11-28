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

// class myComparator
// {
// public:
//     int operator() (Node& value, Node& band, Node& cost) {
//         return p1.getX() > p2.getX();
//     }
// };


struct MinHeap
{
    //First is value and second is weight
    vector<iPair> arrHeap;

    void setArrSize(int n) {
        arrHeap.resize(n, make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
    }

    //An element of the heap is going UP so that its position is corrected
    void bubble_up(int i) {
        // int i = arrHeap.size() -1;
        while (i > 0 && arrHeap[i].second <= arrHeap[(i-1)/2].second) {
            swap(arrHeap[i], arrHeap[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void heap_insert(iPair value) {
        arrHeap.push_back(value);
        bubble_up(arrHeap.size() -1);
    }

    //An element of the heap goes DOWN so that its position is corrected (== heapify)
    void bubble_down(int i) {
        int left, right, m;
        left = 2*i +1;
        right = 2*i +2;
        m = i;
        //A primeira parte do if é pra testar se a posição existe no array
        if (left < arrHeap.size() && arrHeap[left].second <= arrHeap[m].second)
            m = left;
        if (right < arrHeap.size() && arrHeap[right].second <= arrHeap[m].second)
            m = right;
        if (m != i) {
            swap(arrHeap[i], arrHeap[m]);
            bubble_down(m);
        }
    }

    //In complete binary trees, in general the number of elements that are not leaves is (n / 2) -1
    void build_heap() {
        for (int i = 0; i < (arrHeap.size()/2) - 1; i++) {
            bubble_down(i);
        }
    }

    //Delete root, putting last element on root. and reorder de heap
    void heap_extract() {
        swap(arrHeap[0], arrHeap[arrHeap.size() - 1]);
        arrHeap.pop_back();
        bubble_down(0);
    }

    void heap_update(iPair p) {
        if (arrHeap[p.first].second == std::numeric_limits<int>::max()) 
            heap_insert(p);
        
        else 
            bubble_up(p.first - 1);

        // bool flag;
        // for (int i = 0; i < arrHeap.size() - 1; i++) {
        //     if (arrHeap[i].first == p.first){
        //         flag = true; 
        //         bubble_up(i);
        //         break;
        //     }
        // }
        // if (flag == false) {
        //     heap_insert(p);
        // }
    }

    bool isEmpty()  {
        if (arrHeap.empty())
            return true;
        else 
            return false;
    }
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
        newNode.cost = pow(2, 20)/band;
        adjList[position].push_back(newNode);
    }

    int getGraphSize() {
        return N;
    }

    std::pair<vector<int>, vector<int> > dijkstra(int origin) {
        vector<int> dist(N, std::numeric_limits<int>::max());
        vector<int> prec(N, -1);
        MinHeap pq;
        pq.setArrSize(N);

        //Elo (v, d[v])
        pq.heap_insert(make_pair(origin, 0));
        dist[origin] = 0;
        
        for (int count = 0; count< N; count++) {
            //Get first element and remove it from heap
            int u = pq.arrHeap.front().first;
            pq.heap_extract();

            // 'i' is used to get all adjacent vertices of a vertex 
            list< Node >::iterator i;
            for (i = adjList[u].begin(); i != adjList[u].end(); ++i) {
                int value = i->value;
                int band = i->band;
                int cost = pow(2,20)/band;

                if (dist[u] + cost < dist[value]) {
                    dist[value] = dist[u] + cost;
                    prec[value] = u;
                   
                    pq.heap_update(make_pair(value, dist[value]));
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
    Graph gr;
    pair<vector<int>, vector<int> > distPrec;
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

            distPrec = gr.dijkstra(designated_router);

                // Print shortest distances stored in dist[] 
            printf("Vertex   Distance from Source\n"); 
            for (int i = 0; i < gr.getGraphSize(); ++i) 
                printf("%d \t\t %d\n", i, (distPrec.first)[i]); 

            // gr.showEdges();
            num_nodes = 0; designated_router = 0; cur_neighbor = 0; cur_weight = 0; num_neighbors = 0;
        }
        
    return 0;
}
