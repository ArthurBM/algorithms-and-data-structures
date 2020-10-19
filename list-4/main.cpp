#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

template <typename T>
class Vec {
    private:
        int size=0;
        int capacity=1;
        T* arr=NULL;
    public:
        Vec() {
            arr = (T*) malloc(sizeof(T));
        }
        ~Vec() {
            size=0;
            capacity=0;
            free(arr);
        }
        void push_back(T e) {
            if(size >= capacity) {
                capacity *= 2;
                arr = (T*) realloc(arr, sizeof(T)*capacity);
            }
            arr[size++] = e;
        }
        void pop_back() {
            //Se for falso, parará a execução do programa
            assert(size > 0);
            size--;
        }
        void resize(int n) {
            arr = (T*) realloc(arr, sizeof(T)*n);
        }

        int getSize() { return size; }

        T& operator [](int  i) {
            return arr[i];
        }

        void printArray() {
            for (int i = 0; i < size; i++) {
                cout << arr[i] << " ";
            }
            
        }
};


struct MaxHeap
{
    Vec<int> arrHeap;

    //Um elemento da heap vai SUBINDO para que sua posição seja corrigida
    void bubble_up() {
        int i = arrHeap.getSize() -1;
        while (i > 0 && arrHeap[i] >= arrHeap[(i-1)/2]) {
            swap(arrHeap[i], arrHeap[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void heap_insert(int value) {
        arrHeap.push_back(value);
        bubble_up();
    }

    //Um elemento da heap vai DESCENDO para que sua posição seja corrigida (==heapify)
    void bubble_down(int i) {
        int left, right, m;
        left = 2*i +1;
        right = 2*i +2;
        m = i;
        //A primeira parte do if é pra testar se a posição existe no array
        if (left < arrHeap.getSize() && arrHeap[left] >= arrHeap[m])
            m = left;
        if (right < arrHeap.getSize() && arrHeap[right] >= arrHeap[m])
            m = right;
        if (m != i) {
            swap(arrHeap[i], arrHeap[m]);
            bubble_down(m);
        }
    }

    //CUIDADO COM ESSE N/2 - 1, PODE DAR PAU
    //Em árvores binárias completas, em geral o número de elementos que não são folhas é (n/2)-1
    void build_heap() {
        for (int i = 0; i < (arrHeap.getSize()/2) - 1; i++) {
            bubble_down(i);
        }
    }

    //Deleta a raiz
    void heap_extract() {
        int r = arrHeap[0];
        swap(arrHeap[0], arrHeap[arrHeap.getSize() - 1]);
        arrHeap.pop_back();
        bubble_down(0);
    }
};

int main(int argc, char *argv[]) {
    MaxHeap executing, waiting, ready;
    
    executing.heap_insert(4);
    executing.heap_insert(8);
    executing.heap_insert(5);
    executing.heap_insert(3);
    executing.heap_extract();
    executing.arrHeap.printArray();
    return 0;
}