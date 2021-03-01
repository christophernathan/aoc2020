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

void bin(long n, string &ret)
{
    if (n > 1)
        bin(n >> 1, ret);
 //   cout << (n & 1);
    ret+=to_string(n&1);
}

vector<long> editMem(long &value, string &mask){
    vector<int> variable;
    for (int i=0; i<mask.length();i++){
        if (mask[i]=='1'){
            value = (value & ~(1L<<(35-i))) | (1L<<(35-i));
        }
        else if (mask[i]=='X'){
            variable.push_back(i);
        }
    }
    int numOptions = pow(2,variable.size());
    vector<string> options;
    for (int i=0;i<numOptions;i++){ // all binary representations of potential variable char combinations
        string temp="";
        bin(i,temp);
        string add="";
        while(add.length()+temp.length()!=variable.size()){ add+='0'; }
        options.push_back(add+temp);
    } 

    vector<long> mems;
    for (int i=0;i<numOptions;i++){ // adds 1 mem value to array for each binary representation
        long original=value;
        for (int a=0;a<variable.size();a++){ // changes each variable bit according to current binary representation
            original = (original & ~(1L<<(35-variable.at(a)))) | (((options.at(i))[a]=='1'?1L:0L)<<(35-variable.at(a)));
        }
        mems.push_back(original);
     }
     return mems;
}

void editData(long &value, string &mask){
    for (int i=0; i<mask.length();i++){
        if (mask[i]!='X'){
            value = (value & ~(1L<<(35-i))) | ((mask[i]=='1'?1L:0L)<<(35-i));
        }
    }
}



int main(){
    ifstream file;
    file.open("input14.txt");

    map<long,long> data1;
    map<long,long> data2;
    string input;
    string mask;
    long mem1;
    long value1;
    while (file >> input){
        if (input=="mask"){
            file >> input; file >> mask;
        }
        else {
            mem1 = stoi(input.substr(4,input.length()-5));
            file >> input; file >> value1;
            long value2=value1;
            long mem2=mem1;
            vector<long> mems = editMem(mem2, mask);
            editData(value1,mask);
            data1[mem1] = value1;
            for (int i=0;i<mems.size();i++){
                data2[mems.at(i)] = value2;
            }
        }
    }

    long long sum=0;
    map<long, long>::iterator it;
    for (it = data1.begin(); it!=data1.end();it++){
        sum+=it->second;
    }
    cout << sum << endl;
    sum=0;
    for (it = data2.begin(); it!=data2.end();it++){
        sum+=it->second;
    }
    cout << sum << endl;
}