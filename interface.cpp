#include <bits/stdc++.h>
#include "AVL.hpp"
#include "Graph.hpp"
using namespace std;

int currUserCount;

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
            
        }
        else if(command=="ADD_FRIEND"){
            string user1;ss>>user1;user1=getUser(user1);
            string user2;ss>>user2;user2=getUser(user2);

        }
        else if(command=="LIST_FRIENDS"){
            string user;ss>>user;user=getUser(user);

        }
        else if(command=="SUGGEST_FRIENDS"){
            string user;ss>>user;user=getUser(user);
            int n;ss>>n;
            
        }
        else if(command=="DEGREES_OF_SEPARATION"){
            string user1;ss>>user1;user1=getUser(user1);
            string user2;ss>>user2;user2=getUser(user2);

        }

        else if(command=="ADD_POST"){
            string user;ss>>user;user=getUser(user);

        }
        else if(command=="OUTPUT_POSTS"){
            string user;ss>>user;user=getUser(user);

        }
        else{
            cout<<"Failed: Invalid command"<<endl;
        }
    }
    catch(...){
        cout<<"Exception Caught"<<endl;
    }

}

int main(){
    string line;
    currUserCount=0;
    cout<<"> ";
    while(getline(cin, line)){
        if(line=="EXIT"){
            break;
        }
        getcommand(line);
        cout<<"> ";
    }
}