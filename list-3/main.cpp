#include <bits/stdc++.h>
// #include <string>
#define endl '\n'

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int value;
    int height;
};


// class SplayTree
// {
// private:
//     Node* root = NULL;
// public:
//     //Vai retornar a altura onde o nó estava
// };
struct SplayTree {
    Node* root = NULL;
};

void find(Node* root,  int element) {
    if (root == NULL)
        return;
    else if (element == root->value) 
        cout << root->height << endl;

    else if (element < root->value) 
        find(root->left, element);

    else if (element > root->value) 
        find(root->right, element);
}

Node* insert(Node* root, int element) {
    if (root == NULL) {
        Node *ptr = new Node();
        ptr->value = element;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->height = 1;
        return ptr;
    }

    else if (element < root->value) {
        (root->left)->height += 1;
        root->left = insert(root->left, element);
        
        if ((root->left->value) > root->value) {
            //rotateRight()
        }

        return root;
    }

    else if (element > root->value) {
        (root->right)->height += 1;
        root->right = insert(root->right, element);

        // if ((root->right->value) < root->value) {
        //     //rotateLeft()
        // }

        return root;
    }

    else if (element == root->value) {
        find(root ,element);
    }
}


int main(int argc, char const *argv[])
{
    SplayTree tree1;


    return 0;
}
