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
    map<string,int> userIndex; // mapping user id to the index (assigning)
    vector<AVLTree<string,int>> adjList;//adjacency trees.
public:
    Graph(int V=0){
        this->V=V;
        adjList.resize(V);
    }
    int getUserIndex(string user); //-1 if not there
    int addUser(string user);//false if already there
    void addEdge(int user1,int user2);//do nothing if already there 
    vector<string> getFriends(int user);// returns the list
    vector<string> suggestFriends(int user,int n);//suggest friends
    int degreesOfSeparation(int user1,int user2);//-1 if not connected
};

#endif