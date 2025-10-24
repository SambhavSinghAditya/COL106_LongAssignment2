#ifndef Graph_HPP
#define Graph_HPP
      
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "AVL.hpp"
using namespace std;

//will be storing the graphs in adjacecy list format.

class Graph{
private:
    int V;//number of nodes
    unordered_map<string,int> userIndex; // mapping user id to the index (assigning)
    vector<AVLTree<string,int>> adjList;//adjacency trees.
public:
    Graph(int V=0){
        this->V=V;
        adjList.resize(V);
    }
    int getUserIndex(string user); //-1 if not there
    int addUser(string user);//-1 if already there
    int addEdge(string user1,string user2);//-1 if username not there, 0 if already friends, else 1
    vector<string> getFriends(string user);// returns the list
    vector<string> suggestFriends(string user,int n);//suggest friends
    int degreesOfSeparation(string user1,string user2);//-1 if not connected
};

#endif