#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main(){
    ifstream file;
    file.open("input10.txt");
    vector<int> voltages;
    vector<int> necessary;

    voltages.push_back(0);
    necessary.push_back(0);
    int next;
    while (file >> next){
        voltages.push_back(next);
    }
    sort(voltages.begin(), voltages.end());

    int diff1=0, diff3=0;
    for (int i=0; i<voltages.size()-1;i++){
        if (voltages[i]==voltages[i+1]-1){ diff1++; }
        if (voltages[i]==voltages[i+1]-3){ 
            diff3++; 
            if (find(necessary.begin(), necessary.end(), i)==necessary.end()){ necessary.push_back(i); }
            if (find(necessary.begin(), necessary.end(), i+1)==necessary.end()){ necessary.push_back(i+1); }
        }
    }
    if (voltages[voltages.size()-1]-voltages[voltages.size()-2]!=3){ necessary.push_back(voltages.size()-1); }
    diff3++;
    cout << diff1 * diff3 << endl;

    double total = 1;
    for (int i=0; i<necessary.size()-1;i++){
        if (necessary[i+1]-necessary[i]!=1){
            if (voltages[necessary[i+1]]-voltages[necessary[i]]>3){
                total*=pow(2,necessary[i+1]-necessary[i]-1)-1;
            }
            else{
                total*=pow(2,necessary[i+1]-necessary[i]-1);
            }
        }
    }

    cout.precision(20);
    cout << total << endl;
}