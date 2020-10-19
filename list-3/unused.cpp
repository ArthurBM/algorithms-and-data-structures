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
std::pair<Node*, int> bst_delete_min(Node* root) {
    int val;
    if (root->left == NULL) {
        Node* r = root->right;
        val = root->value;
        free(root);
        return std::make_pair(r, val);
    }
    else {
        // std::pair<Node*, int> result = std::make_pair(root->left, val);
        std::pair<Node*, int> result;
        result = bst_delete_min(root->left);
        root->left = result.first;
        val = result.second;
        return std::make_pair(root, val);
    }
}

Node* bst_delete(Node* root, int element) {
    if (root == NULL) 
        return NULL;
    
    else if (element < root->value) {
        height++;
        root->left = bst_delete(root->left, element);
        return root;
    }
    else if (element > root->value) {
        height++;
        root->right = bst_delete(root->right, element);
        return root;
    }

    //else if (element == root->value)
    //Vamos testar se o elemento a ser deletado não possui filho, possui só um filho, ou possui dois filhos
    else {
        
        if ((root->left == NULL) && (root->right == NULL)){
            free(root);
            return NULL;
        }
        //Ou ele não tem nenhum filho ou tem um filho do lado direito
        else if (root->left == NULL) {
            Node *ptr = root->right;
            free(root);
            return ptr;
        }
        else if (root->right == NULL) {
            Node *ptr = root->left;
            free(root);
            return ptr;
        }
        //O nó vai ser o mesmo, você só vai mudar o valor
        else {
            std::pair<Node*, int> result;
            // result = std::make_pair(root->right, root->value);
            result = bst_delete_min(root->right);
            root->right =  result.first;
            root->value = result.second;
            return root;
            
        }
    }
}

int main(int argc, char *argv[]) {
    

    return 0;
}
