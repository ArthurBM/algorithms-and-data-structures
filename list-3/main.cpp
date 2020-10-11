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
Node* bst_search(Node* root,  int element) {
    if (root == NULL)
        return NULL;
    else if (element == root->value) {
        return root;
    }
    else if (element < root->value) {
        height++;
        return bst_search(root->left, element);
    }
    //(element > root->value)
    else {
        height++;
        return bst_search(root->right, element);
    }
}

Node* insert(Node* root, int element) {
    if (root == NULL) {
        Node* ptr = new Node();
        ptr->value = element;
        ptr->left = NULL;
        ptr->right = NULL;
        return ptr;
    }
    else if (element < root->value) {
        height++;
        root->left = insert(root->left, element);
        return root;
    }
    else if (element > root->value) {
        height++;
        root->right = insert(root->right, element);
        return root;
    }
    //Se for igual
    else {
        return root;
    }
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

void pre_order(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->value << " ";
    pre_order(root->left);
    pre_order(root->right);
}

void printInorder(struct Node* root) 
{ 
    if (root == NULL) 
        return; 
  
    /* first recur on left child */
    printInorder(root->left); 
  
    /* then print the data of root */
    cout << root->value << " "; 
  
    /* now recur on right child */
    printInorder(root->right); 
} 



Node* rotate_left(Node* root) {
    Node* ptr = root->right;
    root->right = ptr->left;
    ptr->left = root;
    return ptr;
}

Node* rotate_right(Node* root) {
    Node* ptr = root->left;
    root->left = ptr->right;
    ptr->right = root;
    return ptr;
}

//Lembre que se o algoritmo não achar o valor desejado ele retorna o último valor acessado
//NA MAIN, COLOQUE UMA CHECAGEM SE O ELEMENTO FOI ACHADO
Node* splay(Node* root, int element) {
    if (root == NULL || root->value == element)
        return root;

    //Left
    if (element < root->value) {
        //O elemento não está na árvore
        if (root->left == NULL) {
            return root;
        }
        //Left - Left
        if (element < (root->left)->value) {
            //This first part is just to get to the desired element
            (root->left)->left = splay((root->left)->left, element);
            //PODE DAR ERRADO AQUI (Acho que tá de boa mesmo, pois não fica um ponteiro apontando pra outro. 
            //Na prática root aponta para o mesmo endereço de memória de rotate_right(root)
            root = rotate_right(root);
        }
        //Left - Right
        else if (element > root->value) {
            root->left->right = splay(root->left->right, element);

            if ((root->left)->right != NULL) 
                root->left = rotate_left(root->left);
        }

        return (root->left == NULL) ? root : rotate_right(root);
    }
    //Right
    else {
        if (root->right == NULL)
            return root;
        //Right - Left
        if (element < (root->right)->value) {
            (root->right)->left = splay((root->right)->left, element);

            if ((root->right)->left != NULL)
                root->right = rotate_right(root->right);
        }
        //Right - Right
        else if (element > (root->right)->value) {
            (root->right)->right = splay((root->right)->right, element);
            root = rotate_left(root);
        }

        return (root->right == NULL) ? root : rotate_left(root);
    }

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
            height = 0;
            if (bst_search(tree1.root, treeValue) != NULL){
                tree1.root = splay(tree1.root, treeValue);
            }
        }
        else if (fstWord == "DEL") {
            cin >> treeValue;
            height = 0;
            tree1.root = bst_delete(tree1.root, treeValue);
            cout << height << endl;
        }
        else if (fstWord == "PREO") {
            height = 0;
            pre_order(tree1.root);
            cout << "\n";
            printInorder(tree1.root);
            cout << "\n";
        }
    }

    return 0;
}
