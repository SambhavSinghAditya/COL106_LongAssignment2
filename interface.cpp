#include <bits/stdc++.h>
#include "AVL.hpp"
#include "Graph.hpp"
#include "Posts.hpp"
using namespace std;


int currUserCount;
Graph Network;
Posts PostsManager;

string getUser(string user){
    for (int i=0; i<user.length(); i++) {
        if (user[i]>='A' && user[i]<='Z') {
            user[i]=user[i]+32;
        }
    }
    return user;
}

void getcommand(string line){
    stringstream ss(line);
    string command;
    try{
        ss>>command;
        if(command=="ADD_USER"){
            string user;ss>>user;user=getUser(user);
            int r=Network.addUser(user);
            if(r==-1){
                cout<<" Failed: User already exists"<<endl;
            }
            else{
                PostsManager.addUser(r);
                currUserCount++;
                cout<<" Success: New User Added"<<endl;
            }
        }
        else if(command=="ADD_FRIEND"){
            string user1;ss>>user1;user1=getUser(user1);
            string user2;ss>>user2;user2=getUser(user2);
            int r=Network.addEdge(user1,user2);
            if(r==-1)cout<<" Failed: One or both users do not exist"<<endl;
            else if(r==0) cout<<" Users are already friends"<<endl;
            else cout<<" Success: Users are now friends"<<endl;
        }
        else if(command=="LIST_FRIENDS"){
            string user;ss>>user;user=getUser(user);
            vector<string> friends=Network.getFriends(user);
            for(auto f:friends){
                cout<<" "<<f<<endl;
            }
        }
        else if(command=="SUGGEST_FRIENDS"){
            string user;ss>>user;user=getUser(user);
            int n;ss>>n;
            vector<string> suggested=Network.suggestFriends(user,n);
            if(suggested.size()==n){
                for(auto s:suggested){
                    cout<<" "<<s<<endl;
                }
            }
            else{
                cout<<" No more than "<<suggested.size()<<" suggestions available, for users being limited."<<endl;// users with 0 mutuals is not included in the case
                for(auto s:suggested){
                    cout<<" "<<s<<endl;
                }
            }
        }
        else if(command=="DEGREES_OF_SEPARATION"){
            string user1;ss>>user1;user1=getUser(user1);
            string user2;ss>>user2;user2=getUser(user2);
            cout<<Network.degreesOfSeparation(user1,user2)<<endl;
        }

        else if(command=="ADD_POST"){
            string user;ss>>user;user=getUser(user);
            string text;getline(ss,text);
            int userIndex=Network.getUserIndex(user);
            if(userIndex==-1)cout<<" Failed: User invalid"<<endl;
            else{
                bool r=PostsManager.addPost(userIndex,text);
                if(r)cout<<" Success: Post added"<<endl;
                else cout<<" Failed: Post cant be created"<<endl;
            }
        }
        else if(command=="OUTPUT_POSTS"){
            string user;ss>>user;user=getUser(user);
            int n;ss>>n; 
            int userIndex=Network.getUserIndex(user);
            if(userIndex==-1)cout<<" Failed: User invalid"<<endl;
            else{

                vector<string> posts=PostsManager.getPosts(userIndex,n);
                if(posts.size()<n && n!=-1){
                    cout<<"No more than "<<posts.size()<<" posts available."<<endl;
                }
                for(auto p:posts){
                    cout<<p<<endl;
                }
            }
        }
        else{
            cout<<" Failed: Invalid command"<<endl;
        }
    }
    catch(exception& e){
        cout<<" Error: "<<e.what()<<endl;
    }

}

int main(){
    freopen("input.txt","r",stdin);
    string line;
    currUserCount=0;
    cout<<"> ";
    while(getline(cin, line)){
        cout<<line<<endl;
        if(line=="EXIT"){
            break;
        }
        getcommand(line);
        cout<<"> ";
    }
}