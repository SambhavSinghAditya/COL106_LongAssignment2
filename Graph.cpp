#include "Graph.hpp"
using namespace std;


int Graph::getUserIndex(string user){
    if(userIndex.find(user)==userIndex.end()){
        return -1;
    }
    return userIndex[user];
}

int Graph::addUser(string user){
    if(userIndex.find(user)!=userIndex.end()){
        return -1;
    }
    userIndex[user]=V;
    adjList.push_back(vector<int>());
    V++;
    return userIndex[user];
}