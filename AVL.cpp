#include "AVL.hpp"
using namespace std;

template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(Key k,Value v)
    : key(k), value(v), left(nullptr), right(nullptr), height(1) {}

template<typename Key, typename Value>
int AVLTree<Key, Value>:: height(AVLNode<Key, Value>* node) {
    return node ? node->height : 0;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>:: getBalance(AVLNode<Key, Value>* node) {
    return node ? height(node->left) - height(node->right) : 0;//getting the value of the balace factor

}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* y) {
    // rotating right
    AVLNode<Key, Value>* x=y->left;
    AVLNode<Key, Value>* T2=x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* x) {//left rotation
    AVLNode<Key, Value>* y = x->right;
    AVLNode<Key, Value>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insert(AVLNode<Key, Value>* node,  Key key,  Value value) {
    if (!node)
        return new AVLNode<Key, Value>(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else {
        node->value = value; // update value if key exists
        return node;
    }
    // cout<<node->heightd<<endl;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    //now i need to balance the structure again.
    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::minValueNode(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::remove(AVLNode<Key, Value>* node,  Key key) {
    if (!node)
        return node;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (!node->left || !node->right) {
            AVLNode<Key, Value>* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            // minimum element of right at top and its left child is same as the previous node.
            AVLNode<Key, Value>* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node)
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::find(AVLNode<Key, Value>* node, Key key) {
    if (!node)
        return nullptr;
    if (key == node->key)
        return node;
    if (key < node->key)
        return find(node->left, key);
    else
        return find(node->right, key);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::clear(AVLNode<Key, Value>* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree() : root(nullptr) {}

template<typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
    clear(root);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(Key key, Value value) {
    root = insert(root, key, value);
}

template<typename Key, typename Value>
AVLNode<Key,Value>* AVLTree<Key,Value>::getRoot(){
    return root;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(Key key) {
    root = remove(root, key);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::find(Key key) {
    AVLNode<Key, Value>* node = find(root, key);
        if (node) {
            return node;
        }
        return nullptr;
}

template<typename Key, typename Value>
vector<string> AVLTree<Key, Value>::getTopN(int n){
    vector<string> result; // iterative inorder traversal....
    stack<AVLNode<Key, Value>*> s;
    AVLNode<Key,Value>* curr=root;
    while(curr!=nullptr or !s.empty()){
        while(curr!=nullptr){
            s.push(curr);
            curr=curr->left;
        }
        curr=s.top();s.pop();
        if constexpr (is_same<Value, string>::value) {
            result.push_back(curr->value);
        } else {
            result.push_back(std::to_string(curr->value));
        }
        if(result.size()==n)break;
        curr=curr->right;
    }
    return result;
}

template<typename Key, typename Value>
vector<string> AVLTree<Key, Value>::getTopNKeys(int n){
    vector<string> result; // iterative inorder traversal....
    stack<AVLNode<Key, Value>*> s;
    AVLNode<Key,Value>* curr=root;
    while(curr!=nullptr or !s.empty()){
        while(curr!=nullptr){
            s.push(curr);
            curr=curr->left;
        }
        curr=s.top();s.pop();
        if constexpr (is_same<Key, string>::value) {
            result.push_back(curr->key);
        } else {
            result.push_back(std::to_string(curr->key));
        }
        if(result.size()==n)break;
        curr=curr->right;
    }
    return result;
}

template class AVLNode<string,int>;
template class AVLNode<time_t,string>;


template class AVLTree<string,int>;
template class AVLTree<time_t,string>;
