#include <iostream>
#include <cstdlib>
 
// Túlio Ferreira Franco Carvalho;

#define BLACK 0
#define RED 1
 
using namespace std;
 
struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};
 
typedef Node *NodePtr;
 
class RBTree {
private:
    NodePtr root;
    NodePtr TNULL;
 
    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }
 
    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL ) {
      return nullptr;
    }
    
    
    if ( key == node->data) {
            return node;
        }
 
        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        } 
        return searchTreeHelper(node->right, key);
    }
    
    int intSearchHelper(NodePtr node, int key) {
        
        if( key == node->data ){
            return 1;
        }
        
        if (node == TNULL) {
            return 0;
        }
        if (key < node->data) {
            return intSearchHelper(node->left, key);
        } 
        return intSearchHelper(node->right, key);
    }
 
    void rbTransplant(NodePtr u, NodePtr v){
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
 
    
    // fix the red-black tree
    void fixInsert(NodePtr k){
        NodePtr u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == RED) {
                    // case 3.1
                    u->color =  BLACK;
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle
 
                if (u->color == RED) {
                    // mirror case 3.1
                    u->color =  BLACK;
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;    
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color =  BLACK;
    }
    
public:
    RBTree() {
        TNULL = new Node;
        TNULL->color =  BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
 
  int intSearch(int k) {
    return intSearchHelper(this->root, k);
  }
 
    // search the tree for the key k
    // and return the corresponding node
    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }
 
    // rotate left at node x
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
 
    // rotate right at node x
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
 
    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(int key) {
        // Ordinary Binary Search Insertion
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED; // new node must be red
 
        NodePtr y = nullptr;
        NodePtr x = this->root;
 
        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
 
        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
 
        // if new node is a root node, simply return
        if (node->parent == nullptr){
            node->color =  BLACK;
            return;
        }
 
        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr) {
            return;
        }
 
        // Fix the tree
        fixInsert(node);
    }
 
    NodePtr getRoot(){
        return this->root;
    }
    
    int max(int a, int b){
        if(a > b) return a;
        return b;
    }
 
        //Função recursiva que retorna a altura do nó chave
    int blackheight(NodePtr root){
        if( root == NULL){
            return -1;
        }
        return (!root->color) * 1 + max(blackheight(root->left),blackheight(root->right)); 
        
    }
 
 
    int Altura( NodePtr root){
        int h_left, h_right;
 
        if( root == NULL){
            return -1;
        }else{
            h_left = Altura(root->left);
            h_right = Altura(root->right);
            if(h_left < h_right){
                return h_right + 1;
            }else{
                return h_left + 1;
            }
        }
    }
 
 
 
 
 
};
 
int main() {
 
    RBTree bst;
    int Number, altura, Number_1, lastNode;
    
    // Inserir valor;
    cin >> Number;
    while(Number > 0){
        bst.insert(Number);
        cin >> Number;
    }
    
    
    // Primeiro input :Altura maxima, altura esquerda, altura direita; 
    cout << bst.Altura(bst.getRoot()) - 1 <<  ", " << bst.Altura(bst.getRoot()->left) << ", " << bst.Altura(bst.getRoot()->right) << endl;
    
    
    // Pesquisar valor, se não achar, irá inserir dentro da arvore;
    cin >> Number_1;
    while(Number_1 > 0){
    if(bst.intSearch( Number_1 ) == 0){
        bst.insert(Number_1);
    } else{
        cout << bst.Altura(bst.searchTree(Number_1)) - 1 << ", " << bst.Altura(bst.searchTree(Number_1)->left) << ", " <<  bst.Altura(bst.searchTree(Number_1)->right) << endl;
    }
    cin >> Number_1;
    }
    
    
    // Recebe o ultimo valor;
    cin >> lastNode;
    
    // Se o valor não for encontrado, vai printar que não foi encontrado;
    // Se achar, printará a quantidade de nós pretos, tomando como raiz o valor do lastNode;
    if(bst.intSearch(lastNode) == 0) {
        cout <<  "Valor nao encontrado" << endl;
    } else{
        cout << bst.blackheight(bst.searchTree(lastNode)) << endl;
    }
 
    delete(bst.getRoot());
 
return 0;
}