#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
#include <utility>
using namespace std;

void handleInstruction(string s, int &dir, pair<int,int> &loc){
    char instruction = s[0];
    int value = stoi(s.substr(1,s.length()));
    switch (instruction){
        case 'N': loc.second+=value; break;
        case 'S': loc.second-=value; break;
        case 'E': loc.first+=value; break;
        case 'W': loc.first-=value; break;
        case 'R': dir+=value/90; dir%=4; break;
        case 'L': dir+=4-(value/90); dir%=4; break;
        case 'F':
            switch (dir){
                case 0: loc.first+=value; break;
                case 1: loc.second-=value; break;
                case 2: loc.first-=value; break;
                case 3: loc.second+=value; break;
            } break;
    }
}

void waypointInstructions(string s, pair<int,int> &waypoint, pair<int,int> &loc){
    char instruction = s[0];
    int value = stoi(s.substr(1,s.length()));
    switch (instruction){
        case 'N': waypoint.second+=value; break;
        case 'S': waypoint.second-=value; break;
        case 'E': waypoint.first+=value; break;
        case 'W': waypoint.first-=value; break;
        case 'F': loc.first+=value*waypoint.first; loc.second+=value*waypoint.second; break;
        default:
            int dir;
            if (instruction=='R'){ dir = value/90; dir%=4; }
            else if (instruction=='L'){ dir = 4-(value/90); }
            int x = waypoint.first; int y = waypoint.second;
            switch (dir){
                case 1: waypoint.first=y; waypoint.second=x*-1; break;
                case 2: waypoint.first=x*-1; waypoint.second=y*-1; break;
                case 3: waypoint.first=y*-1; waypoint.second=x; break;
            }
    }
}

int main(){
    ifstream file;
    file.open("input12.txt");

    pair<int,int> loc1(0,0);
    pair<int,int> loc2(0,0);
    pair<int,int> waypoint(10,1);
    int dir = 0;

    string s;
    while (file >> s){
        handleInstruction(s,dir,loc1);
        waypointInstructions(s,waypoint,loc2);
    }
    int manhattan1= abs(loc1.first) + abs(loc1.second);
    cout << manhattan1 << endl;
    int manhattan2 = abs(loc2.first) + abs(loc2.second);
    cout << manhattan2 << endl;

}