#include <bits/stdc++.h>
// #include <string>
#define endl '\n'

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    Node* father;
    int value;
};

struct SplayTree {
    Node* root = NULL;
};

int height = 0;
Node* father_from_deleted;


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

Node* bst_insert(Node* root, int element) {
    if (root == NULL) {
        Node* ptr = new Node();
        ptr->value = element;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->father = NULL;
        return ptr;
    }
    else if (element < root->value) {
        height++;
        root->left = bst_insert(root->left, element);

        if (root->left != NULL)
            (root->left)->father = root;
        return root;
    }
    else if (element > root->value) {
        height++;
        root->right = bst_insert(root->right, element);
        if (root->right != NULL)
            (root->right)->father = root;

        return root;
    }
    //Se for igual
    else {
        return root;
    }
}
//Apaga o valor mínimo de uma árvore não nula
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
        //Não tem filhos
        if ((root->left == NULL) && (root->right == NULL)){
            free(root);
            return NULL;
        }
        //Tem um filho somente do lado direito
        else if (root->left == NULL) {
            Node *ptr = root->right;
            ptr->father = root->father;
            father_from_deleted = root->father;
            free(root);
            return ptr;
        }
        //Tem um filho somente do lado esquerdo
        else if (root->right == NULL) {
            Node *ptr = root->left;
            ptr->father = root->father;
            father_from_deleted = root->father;
            free(root);
            return ptr;
        }
        //Tem dois filhos
        //O nó vai ser o mesmo, você só vai mudar o valor (Então não precisa atualizar o father)
        else {
            std::pair<Node*, int> result;
            // result = std::make_pair(root->right, root->value);
            result = bst_delete_min(root->right);
            root->right =  result.first;
            root->value = result.second;
            father_from_deleted = root->father;
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

void in_order(struct Node* root) 
{ 
    if (root == NULL) 
        return; 
  
    /* first recur on left child */
    in_order(root->left); 
  
    /* then print the data of root */
    cout << root->value << " "; 
  
    /* now recur on right child */
    in_order(root->right); 
}

void post_order(Node* root) {
    if (root == NULL) {
        return;
    }
    post_order(root->left);
    post_order(root->right);
    cout << root->value << " ";
}


Node* rotate_left(Node* root) {
    Node* ptr = root->right;
    Node* fat = root->father;
    root->right = ptr->left;
    ptr->left = root;

    ptr->father = fat;
    root->father = ptr;
    return ptr;
}

Node* rotate_right(Node* root) {
    Node* ptr = root->left;
    Node* fat = root->father;
    root->left = ptr->right;

    ptr->right = root;

    ptr->father = fat;
    root->father = ptr;
    return ptr;
}

//Assumindo que element estará na bst, pois farei um find antes
// Node* splay_2(Node* root, int element) {
//     //Talvez não precise disso
//     Node* fat = root->father;
//     if (root == NULL)
//         return NULL;

//     else if (element < root->value) {
//         root->left = splay_2(root->left, element);
//         // root = rotate_right(fat);
//         return root;
//     }

//     else if (element > root->value) {
//         root->right = splay_2(root->right, element);
//         // root = rotate_left(fat);
//         return root;
//     }

//     //Se element == root->value
//     else {
//         if (fat == NULL) {
//             return root;
//         }
//         else if ((fat->right)->value == element) {
//             return rotate_left(fat);
//         }
//         else if ((fat->left)->value == element) {
//             return rotate_right(fat);
//         }
//     }
// }

Node* splay_while(Node* root, int element) {
    Node* cursor = bst_search(root, element);
    Node* fat = cursor->father;
    Node* ptr;

    while (cursor  != root) {
        //Se o pai for a raiz
        if (cursor->father == root) {
            if (cursor == fat->right) {
                root = rotate_left(fat);
            }
            else if (cursor == fat->left) {
                root = rotate_right(fat);
            }
            return root;
        }

        //Se o cursor tem um avô
        else {
            //O elemento é filho a direita?
            if (cursor == fat->right) {
                Node* ptr2 = fat->father;
                ptr = rotate_left(fat);
                ptr2->right = ptr;
                ptr->father = ptr2;

                if (ptr->father == NULL){
                    // ptr = rotate_left(ptr->right);
                    return ptr;
                }
                // (fat->father)->right = rotate_left(fat);
            }
            else if (cursor == fat->left) {
                Node* ptr2 = fat->father;
                ptr = rotate_left(fat);
                ptr2->left = ptr;
                ptr->father = ptr2;

                if (ptr->father == NULL){
                    // ptr = rotate_right(ptr->left);
                    return ptr;
                }
                // (fat->father)->left = rotate_right(fat);
            }
        }
        if (cursor != root) {
            cursor = ptr;
        }
    }
    
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
            tree1.root = bst_insert(tree1.root, treeValue);
            cout << height << endl;
            height = 0;
            // if (bst_search(tree1.root, treeValue) != NULL)
            tree1.root = splay_while(tree1.root, treeValue);
            
        }
        else if (fstWord == "DEL") {
            cin >> treeValue;
            height = 0;
            tree1.root = bst_delete(tree1.root, treeValue);
            cout << height << endl;
            height = 0;
            tree1.root = splay(tree1.root, father_from_deleted->value);
        }
        else if (fstWord == "ORD") {
            height = 0;
            cout << "PRE ORDER: ";
            pre_order(tree1.root);
            cout << "\nIN ORDER: ";
            in_order(tree1.root);
            cout << "\nPOST ORDER: ";
            post_order(tree1.root);
            cout << "\n";
        }
    }

    return 0;
}
