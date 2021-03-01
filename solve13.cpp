#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
#include <utility>
using namespace std;

int gcd(long long a, long long b){
    if (a==0){ return b; }
    if (b==0) { return a; }
    long long remainder = a%b;
    return gcd(b,remainder);
}

long long lcm(long long a, long long b){
    return (a*b)/gcd(a,b);
}

int main(){
    ifstream file;
    file.open("input13.txt");

    int earliest; file >> earliest;
    string s; file >> s;

    vector<int> id;
    vector<int> offset;
    int a=0;
    int curr=0;
    for (int i=0;i<s.length();i++){
        if (s[i]==',' || i==s.length()-1){
            string next;
            if (i==s.length()-1){ next = s.substr(curr,i-curr+1); }
            else{ next = s.substr(curr,i-curr); }
            if (next!="x"){ id.push_back(stoi(next)); offset.push_back(a); }
            curr = i+1;
            a++;
        }
    }
    int leastTime = INT_MAX;
    int lowestId = INT_MAX;
    for (int i=0;i<id.size(); i++){
        if (id.at(i)-(earliest%id.at(i)) < leastTime) { leastTime = id.at(i)-(earliest%id.at(i)); lowestId = id.at(i); }
    }
    cout << leastTime*lowestId << endl;


    long long step = id.at(0);
    long long t = id.at(0);
    for (int i=1;i<id.size();i++){
        while (true){
            if ((t+offset.at(i))%id.at(i)==0){ break; }
            t+=step;
        }
        step=lcm(step,id.at(i));
    }
    cout << t << endl;
}