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

class Tile{
    public:
        int id;
        string data[10];
        string originalData[10];
        string finalOrientation[10];
        void setId(int);
        void setData(string[]);
        void setOriginalData(string[]);
        void setFinalOrientation(string[]);
        void rotate();
        void flip();
};

void Tile::setData(string newData[10]){
    for (int i=0;i<10;i++){
        data[i] = newData[i];
    }
}

void Tile::setOriginalData(string newData[10]){
    for (int i=0;i<10;i++){
        originalData[i] = newData[i];
    }
}

void Tile::setFinalOrientation(string newData[10]){
    for (int i=0;i<10;i++){
        finalOrientation[i] = newData[i];
    }
}

void Tile::rotate(){
    string prev[10];
    for (int i=0;i<10;i++){
        prev[i] = data[i];
    }
    for (int a=0;a<10;a++){
        for (int b=0;b<10;b++){
            data[b][9-a] = prev[a][b];
        }
    }
}

void Tile::flip(){
    string prev[10];
    for (int i=0;i<10;i++){
        prev[i] = data[i];
    }
    for (int a=0;a<10;a++){
        for (int b=0;b<10;b++){
            data[a][9-b] = prev[a][b];
        }
    }
}

void rotate(char **map, int size){
    char prev[size][size];
    for (int a=0;a<size;a++){
        for (int b=0;b<size;b++){
            prev[a][b] = map[a][b];
        }
    }
    for (int a=0;a<size;a++){
        for (int b=0;b<size;b++){
            map[b][size-a-1] = prev[a][b];
        }
    }
}

void flip(char **map, int size){
    char prev[size][size];
    for (int a=0;a<size;a++){
        for (int b=0;b<size;b++){
            prev[a][b] = map[a][b];
        }
    }
    for (int a=0;a<size;a++){
        for (int b=0;b<size;b++){
            map[a][size-b-1] = prev[a][b];
        }
    }
}

void findEdges(Tile t, string edges[4]){
    edges[0]=t.data[0]; edges[1]=t.data[9];
    string left="",right="";
    for (int i=0;i<10;i++){
        left+=t.data[i][0]; right+=t.data[i][9];
    }
    edges[2]=left; edges[3]=right;
}

int isNeighbor(string edges[4], Tile &t){
    string currEdges[4];
    findEdges(t, currEdges);
    for (int a=0;a<4;a++){
        for (int b=0;b<4;b++){
            if (edges[a]==currEdges[b]){
                switch (a){
                    case 0:
                        switch (b){
                            case 0: t.flip(); t.rotate(); t.rotate(); break;
                            case 2: t.rotate(); t.rotate(); t.rotate(); break;
                            case 3: t.rotate(); t.flip(); break;
                        } break;
                    case 1:
                        switch (b){
                            case 1: t.flip(); t.rotate(); t.rotate(); break;
                            case 2: t.rotate(); t.flip(); break;
                            case 3: t.rotate(); t.rotate(); t.rotate(); break;
                        } break;
                    case 2:
                        switch (b){
                            case 0: t.rotate(); break;
                            case 1: t.flip(); t.rotate(); t.rotate(); t.rotate(); break;
                            case 2: t.rotate(); t.flip(); t.rotate(); break;
                        } break; 
                    case 3:
                        switch (b){
                            case 0: t.flip(); t.rotate(); t.rotate(); t.rotate(); break;
                            case 1: t.rotate(); break;
                            case 3: t.rotate(); t.flip(); t.rotate(); break;
                        }
                }
                return a;
            }
        }
    }
    return -1;
}

int isCorner(Tile query, vector<Tile> &tiles){
    int neighbors = 0;
    string edges[4];
    findEdges(query, edges);
    for (Tile t : tiles){
        if (query.id!=t.id){
            for (int i=0;i<8;i++){
                if (isNeighbor(edges,t)!=-1){ neighbors++; break; }
                i==3?t.rotate():t.flip();
            }
        }
    }
    return neighbors;
}

vector<Tile> setFinalOrientations(Tile &prevTile, vector<Tile> &tiles, map<int,pair<int,int>> &finalOrder, vector<pair<int,vector<string>>> &finalOrientations){
    vector<Tile> toHandle;
    for (Tile currTile : tiles){
        if (finalOrder.find(currTile.id)==finalOrder.end() && prevTile.id!=currTile.id){
            string prevEdges[4], currEdges[4];
            findEdges(prevTile, prevEdges); findEdges(currTile, currEdges);
            int prevCol = finalOrder[prevTile.id].first, prevRow = finalOrder[prevTile.id].second;
            for (int i=0;i<8;i++){
                int neighboring = isNeighbor(prevEdges,currTile);
                if (neighboring!=-1){
                    vector<string> orientation;
                    for (int i=0;i<10;i++){
                        orientation.push_back(currTile.data[i]);
                    }
                    finalOrientations.push_back(make_pair(currTile.id,orientation));
                    switch (neighboring){
                        case 0: finalOrder.insert({currTile.id, make_pair(prevCol, prevRow+1)});
                        case 1: finalOrder.insert({currTile.id, make_pair(prevCol, prevRow-1)});
                        case 2: finalOrder.insert({currTile.id, make_pair(prevCol-1, prevRow)});
                        case 3: finalOrder.insert({currTile.id, make_pair(prevCol+1, prevRow)});
                    }
                    toHandle.push_back(currTile);
                    break;
                }
                i==3?currTile.flip():currTile.rotate();
            }
        }
    }
    return toHandle;
}

int findMonsters(char **map, int size){
    int monsters=0;
    for (int a=0;a<size-2;a++){
        for (int b=0;b<size-19;b++){
            if (map[a][b+18]=='#'&&map[a+1][b]=='#'&&map[a+1][b+5]=='#'&&map[a+1][b+6]=='#'&&map[a+1][b+11]=='#'&&map[a+1][b+12]=='#'&&map[a+1][b+17]=='#'&&map[a+1][b+18]=='#'&&map[a+1][b+19]=='#'&&map[a+2][b+1]=='#'&&map[a+2][b+4]=='#'&&map[a+2][b+7]=='#'&&map[a+2][b+10]=='#'&&map[a+2][b+13]=='#'&&map[a+2][b+16]=='#'){
                monsters++;
            }
        }
    }
    return monsters;
}

int main(){
    ifstream file;
    file.open("input20.txt");

    vector<Tile> tiles;

    string s;
    int id;
    while (file >> s){
        if (s=="Tile"){
            file >> s;
            id = stoi(s.substr(0,s.length()-1));
            string data[10];
            for (int i=0;i<10;i++){
                file >> s;
                data[i]=s;
            }
            Tile t;
            t.id = id;
            t.setData(data);
            t.setOriginalData(data);
            tiles.push_back(t);
        }
    }

    long product = 1;
    for (Tile t : tiles){
        int neighbors = isCorner(t, tiles);
        if (neighbors==2){ product*=t.id; }
    }

    cout << product << endl;

    map<int,pair<int,int>> finalOrder;
    vector<pair<int,vector<string>>> finalOrientations;
    tiles.front().setFinalOrientation(tiles.front().data);
    finalOrder.insert({tiles.front().id,make_pair(0,0)});
    vector<string> orientation;
    for (int i=0;i<10;i++){
        orientation.push_back(tiles.front().data[i]);
    }
    finalOrientations.push_back(make_pair(tiles.front().id,orientation));
    vector<Tile> toHandle; toHandle.push_back(tiles.front());
    while (finalOrder.size()!=tiles.size()){
        vector<Tile> queue;
        for (Tile t : toHandle){
            vector<Tile> add = setFinalOrientations(t, tiles, finalOrder, finalOrientations);
            for (Tile next : add){
                cout << next.id << endl;
                for (string s : next.data){
                    cout << s << endl;
                } cout << endl;
                for (Tile setFinal : tiles){
                    if (setFinal.id==next.id){
                        cout << "TRANSFERRING" << endl;
                        setFinal.setFinalOrientation(next.data);
                        for (string s : setFinal.finalOrientation){
                            cout << s << endl;
                        } cout << endl;
                    }
                }
                queue.push_back(next);
            }
        }
        for (Tile t : queue){
            toHandle.push_back(t);
        }
    }

    for (auto it=finalOrder.begin();it!=finalOrder.end();it++){
        cout << it->second.first << " " << it->second.second << endl;
    }


    int smallestX = 2147483647, largestX = -2147483647, smallestY = 2147483647, largestY = -2147483647;
    for (auto it=finalOrder.begin();it!=finalOrder.end();it++){
        if (it->second.first<smallestX){ smallestX = it->second.first; }
        if (it->second.first>largestX){ largestX = it->second.first; }
        if (it->second.second<smallestY){ smallestY = it->second.second; }
        if (it->second.second>largestY){ largestY = it->second.second; }
    } 

    int size = ((largestX-smallestX)+1)*8;
    char **finalMap;
    for (int i=0;i<size;i++){
        finalMap[i] = new char[size];
    }

    int subsetRow=0, subsetCol=0;

    for (int a=largestY;a>=smallestY;a--){
        for (int b=smallestX;b<=largestX;b++){
            for (auto it=finalOrder.begin();it!=finalOrder.end();it++){
                if (it->second.first==b && it->second.second==a){
                    vector<string> curr;
                    for (pair<int,vector<string>> p : finalOrientations){
                        if (p.first==it->first){ curr = p.second; break; }
                    }
                    for (int y=1;y<9;y++){
                        for (int x=1;x<9;x++){
                            finalMap[subsetRow+y-1][subsetCol+x-1] = curr.at(y)[x];
                        }
                    }
                    break;
                }
            }
            subsetCol+=8;
        }
        subsetCol=0;
        subsetRow+=8;
    }

    long numHashes=0;
    for (int a=0;a<size;a++){
        for (int b=0;b<size;b++){
            if (finalMap[a][b]=='#'){ numHashes++; }
        }
    }

    for (int i=0;i<8;i++){
        int monsters=findMonsters(finalMap,size);
        if (monsters!=0){
            cout << numHashes-(15*monsters) << endl; break;
        }
        i==3?flip(finalMap,size):rotate(finalMap,size);
    }
}