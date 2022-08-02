#include <iostream>
#include <cstdlib>
 
#define BLACK 1
#define RED 0
 
#define left 0
#define right 1
 
// Túlio Ferreira Franco Carvalho
 
using namespace std;
 
struct Node {
    int data, color;;
    Node *parent;
    Node *child[2];
    
};
 
typedef Node *NodePtr;
 
class RBTree {
private:
    NodePtr root;
    NodePtr TNULL;
 
    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = 0;
        node->parent = parent;
        node->child[left] = nullptr;
        node->child[right] = nullptr;
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
            return searchTreeHelper(node->child[left], key);
        } 
        return searchTreeHelper(node->child[right], key);
    }
    
    int intSearchHelper(NodePtr node, int key) {
        
        if( key == node->data ){
            return 1;
        }
        
        if (node == TNULL) {
            return 0;
        }
        if (key < node->data) {
            return intSearchHelper(node->child[left], key);
        } 
        return intSearchHelper(node->child[right], key);
    }
 
    void fixDelete(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->child[left]) {
                s = x->parent->child[right];
                if (s->color == RED) {
                    // case 3.1
                    s->color =  BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->child[right];
                }
 
                if (s->child[left]->color == BLACK && s->child[right]->color == BLACK) {
               
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->child[right]->color == BLACK) {
                    
                        s->child[left]->color =  BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->child[right];
                    } 
 
                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color =  BLACK;
                    s->child[right]->color =  BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->child[left];
                if (s->color == RED) {
                
                    s->color =  BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->child[left];
                }
 
                if (s->child[right]->color == BLACK && s->child[right]->color == BLACK) {
                
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->child[left]->color == BLACK) {
                    
                        s->child[right]->color =  BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->child[left];
                    } 
 
                
                    s->color = x->parent->color;
                    x->parent->color =  BLACK;
                    s->child[left]->color =  BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            } 
        }
        x->color =  BLACK;
    }
 
 
    void rbTransplant(NodePtr u, NodePtr v){
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->child[left]){
            u->parent->child[left] = v;
        } else {
            u->parent->child[right] = v;
        }
        v->parent = u->parent;
    }
 
    void deleteNodeHelper(NodePtr node, int key) {
    
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL){
            if (node->data == key) {
                z = node;
            }
 
            if (node->data <= key) {
                node = node->child[right];
            } else {
                node = node->child[left];
            }
        }
 
        y = z;
        int y_original_color = y->color;
        if (z->child[left] == TNULL) {
            x = z->child[right];
            rbTransplant(z, z->child[right]);
        } else if (z->child[right] == TNULL) {
            x = z->child[left];
            rbTransplant(z, z->child[left]);
        } else {
            y = minimum(z->child[right]);
            y_original_color = y->color;
            x = y->child[right];
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->child[right]);
                y->child[right] = z->child[right];
                y->child[right]->parent = y;
            }
 
            rbTransplant(z, y);
            y->child[left] = z->child[left];
            y->child[left]->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK){
            fixDelete(x);
        }
    }
    
    void fixInsert(NodePtr k){
        NodePtr u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->child[right]) {
                u = k->parent->parent->child[left];
                if (u->color == RED) {
                
                    u->color =  BLACK;
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->child[left]) {
                    
                        k = k->parent;
                        rightRotate(k);
                    }
                
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->child[right];
 
                if (u->color == RED) {
                
                    u->color =  BLACK;
                    k->parent->color =  BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;    
                } else {
                    if (k == k->parent->child[right]) {
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
        TNULL->child[left] = nullptr;
        TNULL->child[right] = nullptr;
        root = TNULL;
    }
 
  int intSearch(int k) {
    return intSearchHelper(this->root, k);
  }
 
    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }
 
    NodePtr minimum(NodePtr node) {
        while (node->child[left] != TNULL) {
            node = node->child[left];
        }
        return node;
    }
 
    NodePtr maximum(NodePtr node) {
        while (node->child[right] != TNULL) {
            node = node->child[right];
        }
        return node;
    }
 
    NodePtr successor(NodePtr x) {
        if (x->child[right] != TNULL) {
            return minimum(x->child[right]);
        }
 
        NodePtr y = x->parent;
        while (y != TNULL && x == y->child[right]) {
            x = y;
            y = y->parent;
        }
        return y;
    }
 
 
    NodePtr predecessor(NodePtr x) {
        if (x->child[left] != TNULL) {
            return maximum(x->child[left]);
        }
 
        NodePtr y = x->parent;
        while (y != TNULL && x == y->child[left]) {
            x = y;
            y = y->parent;
        }
        return y;
    }
 
    void leftRotate(NodePtr x) {
        NodePtr y = x->child[right];
        x->child[right] = y->child[left];
        if (y->child[left] != TNULL) {
            y->child[left]->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->child[left]) {
            x->parent->child[left] = y;
        } else {
            x->parent->child[right] = y;
        }
        y->child[left] = x;
        x->parent = y;
    }
 
    void rightRotate(NodePtr x) {
        NodePtr y = x->child[left];
        x->child[left] = y->child[right];
        if (y->child[right] != TNULL) {
            y->child[right]->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->child[right]) {
            x->parent->child[right] = y;
        } else {
            x->parent->child[left] = y;
        }
        y->child[right] = x;
        x->parent = y;
    }
 
    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->child[left] = TNULL;
        node->child[right] = TNULL;
        node->color = RED;
 
        NodePtr y = nullptr;
        NodePtr x = this->root;
 
        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->child[left];
            } else {
                x = x->child[right];
            }
        }
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->child[left] = node;
        } else {
            y->child[right] = node;
        }
        if (node->parent == nullptr){
            node->color =  BLACK;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        fixInsert(node);
    }
 
    NodePtr getRoot(){
        return this->root;
    }
    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }
    
    int max(int a, int b){
        if(a > b) return a;
        return b;
    }
    int redHeight(NodePtr root){
        int h_left, h_right;
 
        if( root == NULL){
            return 0;
        }
        return (!root->color) * 1 + max(redHeight(root->child[left]),redHeight(root->child[right])); 
        
    }
 
 
    int heightMax( NodePtr root){
        int h_left, h_right;
 
        if( root == NULL){
            return -1;
        }else{
            h_left = heightMax(root->child[left]);
            h_right = heightMax(root->child[right]);
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
    cin >> Number;
    while(Number > 0){
        bst.insert(Number);
        cin >> Number;
    }
    cout << bst.heightMax(bst.getRoot()) - 1 <<  ", " << bst.heightMax(bst.getRoot()->child[left]) << ", " << bst.heightMax(bst.getRoot()->child[right]) << endl;
    cin >> Number_1;
    while(Number_1 > 0){
    if(bst.intSearch( Number_1 ) == 0){
        bst.insert(Number_1);
    } else{
        cout << bst.heightMax(bst.searchTree(Number_1)) - 1 << ", " << bst.heightMax(bst.searchTree(Number_1)->child[left])<< ", " <<  bst.heightMax(bst.searchTree(Number_1)->child[right]) << endl;
        bst.deleteNode(Number_1);
    }
    cin >> Number_1;
    }
    cin >> lastNode;
    if(bst.intSearch(lastNode) == 0) {
        cout <<  "Valor nao encontrado" << endl;
    } else{
        cout << bst.redHeight(bst.searchTree(lastNode)) << endl;
    }
    delete(bst.getRoot());
return 0;
}