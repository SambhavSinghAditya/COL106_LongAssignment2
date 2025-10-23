#ifndef AVL_HPP
#define AVL_HPP

#include <vector>
using namespace std;

template<typename Key, typename Value>
struct AVLNode {
    Key key;
    Value value;// this is the text of post.
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(Key k,  Value v);
};

template<typename Key, typename Value>
class AVLTree {// using this class as the bucket for hashmap.
private:
    AVLNode<Key, Value>* root;
    int height(AVLNode<Key, Value>* node);
    int getBalance(AVLNode<Key, Value>* node);
    AVLNode<Key,Value>* rightRotate(AVLNode<Key,Value>*y);
    AVLNode<Key,Value>* leftRotate(AVLNode<Key,Value>* x) ;
    AVLNode<Key,Value>* insert(AVLNode<Key,Value>*node,Key key,Value value);
    AVLNode<Key,Value>* minValueNode(AVLNode<Key,Value>* node);
    AVLNode<Key,Value>* remove(AVLNode<Key,Value>* node,Key key) ;
    AVLNode<Key,Value>* find(AVLNode<Key,Value>* node,Key key) ;
    void clear(AVLNode<Key, Value>* node) ;

public:
    AVLTree();
    ~AVLTree();
    void insert(Key key, Value value);//O(logn)
    AVLNode<Key,Value>* getRoot();
    void remove(Key key); //O(logn)
    AVLNode<Key,Value>* find(Key key);// O(logn)
    vector<string> getTopN(int n); // O(min(n,logm)) where m is number of nodes in the tree.}} will give all of them if there is -1...
};

#endif