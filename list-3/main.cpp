#include <bits/stdc++.h>
// #include <string>
#define endl '\n'

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int value;
};

int height = 0;

struct SplayTree {
    Node* root = NULL;
};

void find(Node* root,  int element) {
    if (root == NULL)
        return;
    else if (element == root->value) 
        return;

    else if (element < root->value){
        height++;
        find(root->left, element);
    }
    else if (element > root->value) {
        height++;
        find(root->right, element);
    }
}

//Não vai precisar dessa maracutaia toda aí dentro, vou fazer o splay como um método separado mesmo
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
    if (root->left == NULL) {
        Node* r = root->right;
        int val = root->value;
        free(root);
        return std::make_pair(r, val);
    }
    else {
        std::pair<Node*, int> result = bst_delete_min(root->left);
        return std::make_pair(result.first, result.second);
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
        //Ou ele não tem nenhum filho ou tem um filho od lado direito
        if (root->left == NULL) {
            Node *ptr = root->right;
            free(root);
            return ptr;
        }
        else if (root->right == NULL) {
            Node *ptr = root->left;
            free(root);
            return ptr;
        }
        //ATENTE A ESSE CASO QUANDO FOR FAZER A ROTAÇÃO
        //O nó vai ser o mesmo, você só vai mudar o valor
        //ESSA PARTE NÃO ESTÁ FUNCIONANDO, ELE NÃO ESTÁ DELETANDO O ELEMENTO
        else {
            std::pair<Node*, int> result;
            result = std::make_pair(root->right, root->value);
            result = bst_delete_min(root->right);
            return root;
            // std::make_pair(root->right, root->value) = bst_delete_min(root->right);
        }
    }
}

void splay(Node* root, int element) {

}


int main(int argc, char const *argv[])
{
    SplayTree tree1;
    string fstWord = "";
    int treeValue = 0;

    while (fstWord != "END")
    {
        cin >> fstWord;

        if (fstWord == "FND") {
            cin >> treeValue;
            height = 0;
            find(tree1.root, treeValue);
            cout << height << endl;
        }

        else if (fstWord == "INS") {
            cin >> treeValue;
            height = 0;
            tree1.root = insert(tree1.root, treeValue);
            cout << height << endl;
        }
        else if (fstWord == "DEL") {
            cin >> treeValue;
            height = 0;
            tree1.root = bst_delete(tree1.root, treeValue);
            cout << height << endl;
        }
    }

    return 0;
}
