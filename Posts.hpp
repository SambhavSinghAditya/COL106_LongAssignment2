#ifndef Posts_HPP
#define Posts_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "AVL.hpp"
using namespace std;

//will be storing the graphs in adjacecy list format.

class Posts{
private:
    vector<AVLTree<time_t,string>> AVLposts;
    int n;//size of the vector
public:
    Posts(int n=0);
    bool addUser(int userIndex);//false if already there
    bool addPost(int userIndex, string text);// O(log m) true if success
    vector<string> getPosts(int userIndex, int n); // if n is -1 then get all posts O(min(n,logm)) where m is number of post of the user.
    void deletePost(int userIndex, string text);// extra to be done if i have time
};

#endif