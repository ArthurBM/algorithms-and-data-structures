#include <bits/stdc++.h>
#include<math.h>
#include <iostream>
#include <queue>
#include<set>
#include<list>
#include<vector>
#define endl '\n'
#define infin std::numeric_limits<int>::max()

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
        arrHeap.resize(n, make_pair(infin, infin));
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
        if (arrHeap[p.first].second == infin) 
            heap_insert(p);
        
        else 
            bubble_up(p.first - 1);
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

    std::tuple<vector<int>, vector<int> > dijkstra (int origin) {
        vector<int> dist(N, infin);
        vector<int> prec(N, -1);
        MinHeap pq;
        pq.setArrSize(N);

        //Elo (v, d[v])
        pq.heap_insert(make_pair(origin, 0));
        dist[origin] = 0;
        
        for (int count = 0; count < N; count++) {
            //Get first element and remove it from heap
            if (pq.arrHeap.front().first != infin) {
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

                    else if (dist[u] + cost == dist[value]) {
                        if (u < value) {
                            dist[value] = dist[u] + cost;
                            prec[value] = u;

                            pq.heap_update(make_pair(value, dist[value]));
                        }
                    }
                }
            }
        }

        return (make_tuple(dist, prec));
    }

};

std::tuple<int, int> num_nodes_and_time_passed (vector<int> dist, vector<int> prec, int emissor, int receptor, int message_size) {
    int i = receptor;
    int count_nodes_passed = 0, time_passed = 0;

    if (receptor != emissor) {
        time_passed = (message_size/dist[i]);
    }
    //Isso supõe que sempre existe um caminho entre emissor e receptor
    //Como i é inicializado como receptor, se ele for igual ao emissor, ele nem vai entrar no while
    //O emissor vai ser sempre o DR
    while (i != emissor) {
        
        if (prec[i] == -1) {
            break;
        }

        else {
            if (i != emissor)
                time_passed += (message_size/dist[i]);
            i = prec[i];
            count_nodes_passed++;
        }
    }
    //Segundo parâmetro vai ser o tempo
    return make_tuple(count_nodes_passed, time_passed);
}


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
    vector<int> dist, prec;
    int num_nodes, designated_router;
    int cur_neighbor, cur_weight;
    int num_neighbors;
    int messages_num;
    int emissor, receptor, message_size;
    int num_nodes_passed, time_local;
    int num_nodes_passed2, time_local2;
    int count_global = 0;
    vector<int> emissor_vec, receptor_vec, message_size_vec;

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

            tie(dist, prec) = gr.dijkstra(designated_router);

            cin >> messages_num;
            for (int count = 0; count < messages_num; count++) {
                cin >> emissor >> receptor >> message_size;
                
                emissor_vec.push_back(emissor); receptor_vec.push_back(receptor); message_size_vec.push_back(message_size);
                //Chamar função para saber:
                //1. número de nós intermédios pelos quais a mensagem passa na sua rota do emissor até o receptor (excluindo emissor e receptor)
                //2. O custo total do caminho (Tempo) - emissor até DR + DR até receptor
            }

            cout << "caso " << count_global << ":" <<  endl;
            for (int count2 = 0; count2 < messages_num; count2++) {
                tie(num_nodes_passed, time_local) = num_nodes_and_time_passed(dist, prec, designated_router, emissor_vec[count2], message_size_vec[count2]);
                tie(num_nodes_passed2, time_local2) = num_nodes_and_time_passed(dist, prec, designated_router, receptor_vec[count2], message_size_vec[count2]);

                // cout << "Número de nós / Tempo entre " << emissor_vec[count2] << " e " << receptor_vec[count2] << ": " << (num_nodes_passed + num_nodes_passed2 - 1) << (time_local + time_local2) << endl;
                // printf("Numero de nós / Tempo entre %d e %d: %d, %d\n", emissor_vec[count2], receptor_vec[count2], (num_nodes_passed + num_nodes_passed2 - 1), (time_local + time_local2));
                printf("%d %d\n", (num_nodes_passed + num_nodes_passed2 - 1), (time_local + time_local2));

            }



            // Print shortest distances stored in dist[] 
            // printf("Vertex   Distance from Source   Precursor\n"); 
            // for (int i = 0; i < gr.getGraphSize(); ++i) 
            //     printf("%d \t\t %d \t\t %d\n", i, dist[i], prec[i]); 

            // gr.showEdges();
            num_nodes = 0; designated_router = 0; cur_neighbor = 0; cur_weight = 0; num_neighbors = 0; messages_num = 0;
            emissor = 0; receptor = 0; message_size = 0;
            emissor_vec.clear(); receptor_vec.clear(); message_size_vec.clear();
            count_global++;
            
        }
        
    return 0;
}
