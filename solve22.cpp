#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <utility>
using namespace std;

string listToString(list<int> l){
    string ret="";
    for (int i : l){
        ret+=to_string(i);
    }
    return ret;
}

void playRound(list<int> &player1, list<int> &player2){
    int a = player1.front();
    player1.pop_front();
    int b = player2.front();
    player2.pop_front();
    if (a>b){
        player1.push_back(a);
        player1.push_back(b);
    }
    else{
        player2.push_back(b);
        player2.push_back(a);
    }
}

int recursiveCombat(list<int> &player1, list<int> &player2){
    vector<pair<string,string>> seen;
    while (player1.size()!=0 && player2.size()!=0){
        pair<string,string> curr = make_pair(listToString(player1),listToString(player2));
        if (find(seen.begin(),seen.end(),curr)!=seen.end()){ return 1; }
        seen.push_back(curr);

      /*  for (int i : player1){
            cout << i << " ";
        }
        cout << endl;
        for (int i : player2){
            cout << i << " ";
        }
        cout << endl;*/

        int a = player1.front();
        int b = player2.front();
       // cout << "Player 1 picks: " << a << endl;
       // cout << "Player 2 picks: " << b << endl;
        player1.pop_front();
        player2.pop_front();
        if (a<=player1.size() && b<=player2.size()){
            list<int> p1,p2; auto it1 = player1.begin(); auto it2 = player2.begin();
            for (int i=0;i<a;i++){
                p1.push_back(*it1); it1++;
            }
            for (int i=0;i<b;i++){
                p2.push_back(*it2); it2++;
            }
         /*  for (int i : p1){
                cout << i << " ";
            }
            cout << endl;
            for (int i : p2){
                cout << i << " ";
            }
            cout << endl;*/
            int res = recursiveCombat(p1,p2);
            if (res==1){
                player1.push_back(a);
                player1.push_back(b);
            }
            else{
                player2.push_back(b);
                player2.push_back(a);
            }
        }
        else{
            if (a>b){
                player1.push_back(a);
                player1.push_back(b);
            }
            else{
                player2.push_back(b);
                player2.push_back(a);
            }
        }
    }
    if (player1.size()==0){
        return 2;
    }
    else{
        return 1;
    }
}

int main(){
    ifstream file;
    file.open("input22.txt");

    list<int> player1,player2;

    string s;
    getline(file,s);
    while (file >> s){
        if (s=="Player"){file >> s; break;}
        player1.push_back(stoi(s));
    }
    while (file >> s){
        player2.push_back(stoi(s));
    }

 /*   for (int i : player1){
        cout << i << endl;
    }
    cout << endl;
    for (int i : player2){
        cout << i << endl;
    }*/

    list<int> player1copy = player1, player2copy = player2;

    while (player1.size()!=0 && player2.size()!=0){
        playRound(player1,player2);
    }
    list<int> winner;
    if (player1.size()==0){ winner = player2; }
    else{ winner = player1; }

  /*  for (int i : winner){
        cout << i << endl;
    }*/

    double sum=0;
    int i=1;
    while (winner.size()!=0){
       // cout << i << " " << winner.back() << endl;
        sum+=i*winner.back();
        winner.pop_back();
        i++;
    }
    cout << sum << endl;


    int res = recursiveCombat(player1copy,player2copy);
    if (res==1){ winner = player1copy; }
    else{ winner = player2copy; }
    sum=0;
    i=1;
    while (winner.size()!=0){
        cout << i << " " << winner.back() << endl;
        sum+=i*winner.back();
        winner.pop_back();
        i++;
    }
    cout << sum << endl;
}