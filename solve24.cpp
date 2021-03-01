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

int calcNeighbors(double x, double y, vector<pair<double,double>> black){
    int neighbors=0;
    for (pair<double,double> p : black){
        if (((abs(x-p.first)==0.5 && abs(y-p.second)==1) || (abs(x-p.first)==1 && y==p.second)) && (x!=p.first || y!=p.second)){
            neighbors++;
        }
    }
    return neighbors;
}

vector<pair<double,double>> toChange(vector<pair<double,double>> &black){
    vector<pair<double,double>> toChange;
    double smallestXeven=2147483647; double largestXeven=-2147483648; double smallestXodd=2147483647; double largestXodd=-2147483648; double smallestY=black[0].second; double largestY=black[0].second;
    for (pair<double,double> p : black){
        if ((int)p.second%2==0){
            if (p.first<smallestXeven){ smallestXeven=p.first; }
            if (p.first>largestXeven){ largestXeven=p.first; }
        }
        else{
            if (p.first<smallestXodd){ smallestXodd=p.first; }
            if (p.first>largestXodd){ largestXodd=p.first; }
        }
        if (p.second<smallestY){ smallestY=p.second; }
        if (p.second>largestY){ largestY=p.second; }
    }
    if (smallestXodd<smallestXeven){
        smallestXeven=smallestXodd-1.5; smallestXodd-=1;
    }
    else{
        smallestXodd=smallestXeven-1.5; smallestXeven-=1;
    }
    if (largestXeven>largestXodd){
        largestXodd=largestXeven+=1.5; largestXeven+=1;
    }
    else{
        largestXeven=largestXodd+=1.5; largestXodd+=1;
    }
    smallestY-=1; largestY+=1;

    for (double y=smallestY; y<=largestY; y+=1){
        for (double x=((int)y%2==0?smallestXeven:smallestXodd); x<=((int)y%2==0?largestXeven:largestXodd); x+=1){
            int neighbors = calcNeighbors(x,y,black);
            if (find(black.begin(), black.end(), make_pair(x,y))!=black.end()){
                if (neighbors==0 || neighbors>2){ toChange.push_back(make_pair(x,y)); }
            }
            else{
                if (neighbors==2){ toChange.push_back(make_pair(x,y)); }
            }
        }
    }
    return toChange;
}

void makeChange(vector<pair<double,double>> &black, vector<pair<double,double>> &toChange){
    for (pair<double,double> p : toChange){
        auto it = find(black.begin(), black.end(), p);
        if (it!=black.end()){ black.erase(it); }
        else{ black.push_back(p); }
    }
}

pair<double,double> calcSpace(string s){
    int index=0;
    double x=0;double y=0;
    while (index<s.length()){
        if (s[index]=='n'){
            index++;
            if (s[index]=='e'){ x+=0.5;y+=1; }
            else if (s[index]=='w'){ x-=0.5;y+=1; }
        }
        else if (s[index]=='s'){
            index++;
            if (s[index]=='e'){ x+=0.5;y-=1; }
            else if (s[index]=='w'){ x-=0.5;y-=1; }
        }
        else if (s[index]=='e'){ x+=1; }
        else if (s[index]=='w'){ x-=1; }
        index++;
    }
    return make_pair(x,y);
}

int main(){
    ifstream file;
    file.open("input24.txt");

    vector<pair<double,double>> black;

    string next;
    while (file >> next){
        pair<double,double> temp = calcSpace(next);
        auto it = find(black.begin(),black.end(),temp);
        if (it==black.end()){ black.push_back(temp); }
        else{ black.erase(it); }
    }
    cout << black.size() << endl;

    int days=0;
    while (days!=100){
        vector<pair<double,double>> change = toChange(black);
        makeChange(black,change);
        days++;
    }
    cout << black.size() << endl;
}