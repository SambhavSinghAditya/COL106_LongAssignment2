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
    AVLTree<string,int> newTree;
    adjList.push_back(newTree);
    V++;
    return userIndex[user];
}

int Graph::addEdge(string user1,string user2){
    if(userIndex.find(user1)==userIndex.end() or userIndex.find(user2)==userIndex.end()){
        return -1;
    }
    if(adjList[userIndex[user1]].find(user2)==nullptr){
        adjList[userIndex[user1]].insert(user2,userIndex[user2]);
        adjList[userIndex[user2]].insert(user1,userIndex[user1]);
        return 1;
    }
    else return 0;
}

vector<string> Graph::getFriends(string user){
    return adjList[userIndex[user]].getTopNKeys(-1);
}

vector<string> Graph::suggestFriends(string user,int n){
    // can i do it better than nlonn time
    // what i need to do is get all friends of friends and then sort them according to number of mutual friends. and break the ties alphabetically.
    unordered_map<string,int> mutualFriendCount;  
    vector<string> friends=getFriends(user);
    for(string friendUser:friends){
        mutualFriendCount[friendUser]=-1;
        vector<string> friendsOfFriend=getFriends(friendUser);
        for(string fof:friendsOfFriend){
            if(fof!=user and mutualFriendCount[fof]!=-1){// no need to check if fof is a friend of user as we have already marked them -1
                if(mutualFriendCount.find(fof)==mutualFriendCount.end()){
                    mutualFriendCount[fof]=1;
                }else{
                    mutualFriendCount[fof]++;
                }
            }
        }
    }
    vector<pair<int,string>> candidates;
    for(auto it:mutualFriendCount){
        if(it.second<=0)continue;
        candidates.push_back({it.second,it.first});
    }
    sort(candidates.begin(),candidates.end(),greater<pair<int,string>>());
    vector<string> suggestions;
    for(int i=0;i<n && i<candidates.size();i++){
        suggestions.push_back(candidates[i].second);
    }
    return suggestions;
}

int Graph::degreesOfSeparation(string user1,string user2){
    //bfs from user1 to user2
    if(userIndex.find(user1)==userIndex.end() or userIndex.find(user2)==userIndex.end()){
        return -1;
    }
    if(user1==user2) return 0;
    unordered_map<string,bool> visited;
    queue<pair<string,int>> q;
    q.push({user1,0});
    visited[user1]=true;
    while(!q.empty()){
        pair<string,int> curr=q.front();q.pop();
        string currUser=curr.first;
        int currDist=curr.second;
        vector<string> friends=getFriends(currUser);
        for(string friendUser:friends){
            if(!visited[friendUser]){
                if(friendUser==user2){
                    return currDist+1;
                }
                visited[friendUser]=true;
                q.push({friendUser,currDist+1});
            }
        }
    }
    return -1;
}