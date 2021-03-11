#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
#include <math.h>
#include <utility>
using namespace std;

struct quad{
    int x;int y;int z;int w;
    quad(int first, int second, int third, int fourth){x=first;y=second;z=third;w=fourth;}
};

vector<quad>::iterator contains(vector<quad> &active, quad q){
    for (auto it = active.begin();it!=active.end();it++){
        if (it->x==q.x && it->y==q.y && it->z==q.z && it->w==q.w){ return it; }
    }
    return active.end();
}

int calcActiveNeighbors(int x, int y, int z, vector<tuple<int,int,int>> active){
    int activeNeighbors=0;
    for (int i=0;i<active.size();i++){
        if ((abs(x-get<0>(active[i]))<=1 && abs(y-get<1>(active[i]))<=1 && abs(z-get<2>(active[i]))<=1) && (x!=get<0>(active[i]) || y!=get<1>(active[i]) || z!=get<2>(active[i]))){
            activeNeighbors++;
        }
    }
    return activeNeighbors;
}

int calcActiveNeighbors2(int x, int y, int z, int w, vector<quad> active){
    int activeNeighbors=0;
    for (int i=0;i<active.size();i++){
        if ((abs(x-active[i].x)<=1 && abs(y-active[i].y)<=1 && abs(z-active[i].z)<=1 && abs(w-active[i].w)<=1) && (x!=active[i].x || y!=active[i].y || z!=active[i].z || w!=active[i].w)){
            activeNeighbors++;
        }
    }
    return activeNeighbors;
}

vector<tuple<int,int,int>> toChange(vector<tuple<int,int,int>> active){
    vector<tuple<int,int,int>> toChange;
    int largestX=get<0>(active[0]); int largestY=get<1>(active[0]); int largestZ=get<2>(active[0]); int smallestX=get<0>(active[0]); int smallestY=get<1>(active[0]); int smallestZ=get<2>(active[0]);
    for (int i=1;i<active.size();i++){
        if (get<0>(active[i])>largestX){ largestX = get<0>(active[i]); } if (get<0>(active[i])<smallestX){ smallestX = get<0>(active[i]); }
        if (get<1>(active[i])>largestY){ largestY = get<1>(active[i]); } if (get<1>(active[i])<smallestY){ smallestY = get<1>(active[i]); }
        if (get<2>(active[i])>largestZ){ largestZ = get<2>(active[i]); } if (get<2>(active[i])<smallestZ){ smallestZ = get<2>(active[i]); }
    }
    largestX++; largestY++; largestZ++; smallestX--; smallestY--; smallestZ--;
    for (int x=smallestX;x<=largestX;x++){
        for (int y=smallestY;y<=largestY;y++){
            for (int z=smallestZ;z<=largestZ;z++){
                int activeNeighbors = calcActiveNeighbors(x,y,z,active);
                if((find(active.begin(), active.end(), make_tuple(x,y,z)) != active.end()) && (activeNeighbors!=2 && activeNeighbors!=3)) {
                    toChange.push_back(make_tuple(x,y,z));
                }
                else if ((find(active.begin(), active.end(), make_tuple(x,y,z)) == active.end()) && activeNeighbors==3){ 
                    toChange.push_back(make_tuple(x,y,z));
                }
            }
        }
    }
    return toChange;
}

vector<quad> toChange2(vector<quad> active){
    vector<quad> toChange;
    int largestX=active[0].x; int largestY=active[0].y; int largestZ=active[0].z; int largestW=active[0].w; int smallestX=active[0].x; int smallestY=active[0].y; int smallestZ=active[0].z; int smallestW=active[0].w;
    for (int i=1;i<active.size();i++){
        if (active[i].x>largestX){ largestX = active[i].x; } if (active[i].x<smallestX){ smallestX = active[i].x; }
        if (active[i].y>largestY){ largestY = active[i].y; } if (active[i].y<smallestY){ smallestY = active[i].y; }
        if (active[i].z>largestZ){ largestZ = active[i].z; } if (active[i].z<smallestZ){ smallestZ = active[i].z; }
        if (active[i].w>largestW){ largestW = active[i].w; } if (active[i].w<smallestW){ smallestW = active[i].w; }
    }
    largestX++; largestY++; largestZ++; largestW++; smallestX--; smallestY--; smallestZ--; smallestW--;
    for (int x=smallestX;x<=largestX;x++){
        for (int y=smallestY;y<=largestY;y++){
            for (int z=smallestZ;z<=largestZ;z++){
                for (int w=smallestW;w<=largestW;w++){
                    int activeNeighbors = calcActiveNeighbors2(x,y,z,w,active);
                    if(contains(active,quad(x,y,z,w))!=active.end() && activeNeighbors!=2 && activeNeighbors!=3) {
                        toChange.push_back(quad(x,y,z,w));
                    }
                    else if (contains(active,quad(x,y,z,w))==active.end() && activeNeighbors==3){ 
                        toChange.push_back(quad(x,y,z,w));
                    }
                }
            }
        }
    }
    return toChange;
}

void changeActive(vector<tuple<int,int,int>> &active, vector<tuple<int,int,int>> toChange){
    for (int i=0; i<toChange.size();i++){
        auto it = find(active.begin(), active.end(), toChange[i]);
        if (it != active.end()){
            active.erase(it);
        }
        else{
            active.push_back(toChange[i]);
        }
    }
}

void changeActive2(vector<quad> &active, vector<quad> toChange){
    for (int i=0; i<toChange.size();i++){
        auto it = contains(active,toChange[i]);
        if (it != active.end()){
            active.erase(it);
        }
        else{
            active.push_back(toChange[i]);
        }
    }
}

int main(){
    ifstream file;
    file.open("input17.txt");

    vector<tuple<int,int,int>> active;
    vector<quad> active2;

    string next;
    int col=0;
    while (file >> next){
        for (int i=0;i<next.length();i++){
            if (next[i]=='#'){active.push_back(make_tuple(i,col,0)); active2.push_back(quad(i,col,0,0)); }
        }
        col++;
    }
    for (int i=0;i<6;i++){
        changeActive(active,toChange(active));
        changeActive2(active2,toChange2(active2));
    }
    cout << active.size() << endl;
    cout << active2.size() << endl;
}