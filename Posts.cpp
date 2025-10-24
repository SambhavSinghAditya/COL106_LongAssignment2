#include "Posts.hpp"
using namespace std;

Posts::Posts(int n){
    this->n=n;
    AVLposts.resize(n);
}

bool Posts::addUser(int userIndex){
    if(userIndex!=n){cout<<"User index mismatch in posts class"<<endl;return false;}
    else{
        n++;
        AVLTree<time_t,string> newTree;
        AVLposts.push_back(newTree);
        return true;
    }
}

bool Posts::addPost(int userIndex, string text){
    time_t currTime=time(0);
    AVLposts[userIndex].insert(currTime,text);
    return true;
}

vector<string> Posts::getPosts(int userIndex, int n){
    vector<string> result;
    AVLTree<time_t,string>& tree=AVLposts[userIndex];
    result=tree.getTopN(n);
    return result;
}

void Posts::deletePost(int userIndex, string text){
    //to be done if time is there
}