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

void move(int* cups, int highest, int lowest, int &current){
    int pickup[3];
    int c = current;
    for (int i=0;i<3;i++){
        pickup[i] = cups[c];
        c = cups[c];
    }
    int followingCurrent = cups[c];
    int target = current-1;
    while (target == pickup[0] || target == pickup[1] || target == pickup[2] || target<1){
        target--;
        if (target<lowest){ target=highest; }
    }
    int afterTarget = cups[target];
    cups[current] = followingCurrent;
    cups[target] = pickup[0];
    cups[pickup[2]] = afterTarget;
    current = followingCurrent;
}

int main(){
    ifstream file;
    file.open("input23.txt");

    int cups[10];
    int cups2[1000001];

    string input;
    file >> input;

    for (int i=0;i<input.length()-1;i++){
        cups[input[i]-'0'] = input[i+1]-'0';
        cups2[input[i]-'0'] = input[i+1]-'0';
    }
    cups[input[input.length()-1]-'0'] = input[0]-'0';
    cups2[input[input.length()-1]-'0']=10;
    for (int i=10;i<1000000;i++){
        cups2[i]=i+1;
    }
    cups2[1000000]=input[0]-'0';

    int current = input[0]-'0';
    int current2 = current;

    cout << current << endl;

    for (int i=0;i<100;i++){
        move(cups,9,1,current);
    }
    int c = 1;
    for (int i=0; i<sizeof(cups)/sizeof(cups[0])-1; i++){
        cout << cups[c];
        c=cups[c];
    }
    cout << endl;

    for (int i=0;i<10000000;i++){
        move(cups2,1000000,1,current2);
    }
    int one = cups2[1];
    int two = cups2[one];
    cout << one << " " << two << endl;
    cout << (long)one*two << endl;
}