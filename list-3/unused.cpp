#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int value;
};

int height = 0;

Node* insert(Node* root, int element) {
    if (root == NULL) {
        Node* ptr = new Node();
        ptr->value = element;
        ptr->left = NULL;
        ptr->right = NULL;
        // ptr->height = 1;
        return ptr;
    }

    else if (element < root->value) {
        // (root->left)->height += 1;
        height++;
        root->left = insert(root->left, element);
        
        // if ((root->left->value) > root->value) {
        //     //rotateRight()
        // }

        return root;
    }

    else if (element > root->value) {
        // (root->right)->height += 1;
        height++;
        root->right = insert(root->right, element);

        // if ((root->right->value) < root->value) {
        //     //rotateLeft()
        // }

        return root;
    }

    else {
        cout << height << endl;
        return root;
    }
    
    // else if (element == root->value) {
    //     find(root ,element);
    // }
}

int main(int argc, char *argv[]) {
    

    return 0;
}
