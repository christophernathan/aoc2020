#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
#include <utility>
using namespace std;

void calcChange(vector<vector<char>> &seats, vector<pair<int,int>> &toChange){
    for (int a=1;a<seats.size()-1;a++){
        for (int b=1;b<seats[0].size()-1;b++){
            int numPound=0;
            for (int col=b-1;col>0;col--){
                if (seats[a][col]=='#'){ numPound++; break;}
                else if (seats[a][col]=='L'){ break;}
            }
            for (int col=b+1;col<seats[0].size();col++){
                if (seats[a][col]=='#'){ numPound++; break;}
                else if (seats[a][col]=='L'){ break;}
            }
            for (int row=a+1;row<seats.size();row++){
                if (seats[row][b]=='#'){ numPound++; break;}
                else if (seats[row][b]=='L'){ break;}
            }
            for (int row=a-1;row>0;row--){
                if (seats[row][b]=='#'){ numPound++; break;}
                else if (seats[row][b]=='L'){ break;}
            }
            int row=a-1; int col=b-1;
            while (row>0&&col>0){
                if (seats[row][col]=='#'){ numPound++; break;}
                else if (seats[row][col]=='L'){ break;}
                row--;col--;
            }
            row=a+1; col=b+1;
            while (row<seats.size()&&col<seats[0].size()){
                if (seats[row][col]=='#'){ numPound++; break;}
                else if (seats[row][col]=='L'){ break;}
                row++;col++;
            }
            row=a-1; col=b+1;
            while (row>0&&col<seats[0].size()){
                if (seats[row][col]=='#'){ numPound++; break;}
                else if (seats[row][col]=='L'){ break;}
                row--;col++;
            }
            row=a+1; col=b-1;
            while (row<seats.size()&&col>0){
                if (seats[row][col]=='#'){ numPound++; break;}
                else if (seats[row][col]=='L'){ break;}
                row++;col--;
            }
            if (seats[a][b]=='L'){
                if (numPound==0){
                    toChange.push_back(make_pair(a,b));
                }
            }
            else if (seats[a][b]=='#'){
                if (numPound>=5){
                    toChange.push_back(make_pair(a,b));
                }
            }
        }
    }
}

void changeSeats(vector<vector<char>> &seats, vector<pair<int,int>> &toChange){
    for (int a=0;a<toChange.size();a++){
        int row = toChange[a].first;
        int col = toChange[a].second;
        if (seats[row][col]=='L'){ seats[row][col]='#'; }
        else if (seats[row][col]=='#'){ seats[row][col]='L'; }
    }
}

int main(){
    ifstream file;
    file.open("input11.txt");
    vector<vector<char>> seats;

    string next;
    vector<char> temp;
    file >> next;
    for (int i=0;i<next.length()+2;i++){ temp.push_back('.'); }
    seats.push_back(temp);
    temp.clear();
    temp.push_back('.');
    for (char c : next){ temp.push_back(c); }
    temp.push_back('.');
    seats.push_back(temp);
    while (file >> next){
        vector<char> temp;
        temp.push_back('.');
        for (char c : next){ temp.push_back(c); }
        temp.push_back('.');
        seats.push_back(temp);
    }
    temp.clear();
    for (int i=0;i<seats[0].size();i++){ temp.push_back('.'); }
    seats.push_back(temp);

    vector<pair<int,int>> toChange;

    calcChange(seats, toChange);
    while (toChange.size()!=0){
        changeSeats(seats,toChange);
        toChange.clear();
        calcChange(seats, toChange);
    }

    int count=0;
    for (int a=0;a<seats.size();a++){
        for (int b=0;b<seats[0].size();b++){
            if (seats[a][b]=='#'){ count++; }
        }
    }
    cout << count << endl;

}