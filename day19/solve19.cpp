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

vector<string> _split(string s){
    vector<string> ret;
    int currStart=0;
    for (int i=0;i<s.length();i++){
        if (s[i]==' '){
            ret.push_back(s.substr(currStart,i-currStart));
            currStart=i+1;
        }
    }
    ret.push_back(s.substr(currStart,s.length()-currStart));
    return ret;
}

vector<string> findValid(int rule, map<int,vector<vector<int>>> rules, map<int,string> pureRules){
    vector<string> ret;
    if (rules.find(rule)==rules.end()){
        ret.push_back(pureRules[rule]);
        return ret;
    }
    for (vector<int> subset : rules[rule]){
        vector<vector<string>> options;
        for (int i : subset){
            vector<string> curr = findValid(i,rules,pureRules);
            options.push_back(curr);
        }

        vector<string> individualOptions;
        individualOptions.push_back("");
        for (vector<string> v : options){
            vector<string> newOptions;
            for (string prev : individualOptions){
                string s = prev;
                for (string addition : v){
                    string newString = s+addition;
                    if (newString.length()<=96){
                        newOptions.push_back(s+addition);
                    }
                }
            }
            individualOptions.clear();
            for (string s : newOptions){
                individualOptions.push_back(s);
            }
        }
        for (string s : individualOptions){
            ret.push_back(s);
        }
    }
    return ret;
}

int main(){
    ifstream file;
    file.open("input19.txt");

    map<int,vector<vector<int>>> rules;
    map<int,string> pureRules;
    vector<string> toCheck;

    string s;
    while (getline(file,s)){
        vector<string> split = _split(s);
        if (split.size()==1){
            toCheck.push_back(s);
        }
        else if (split.size()==2 && split.back()[0]=='\"'){
            pureRules[stoi(split.front().substr(0,split.front().length()-1))] = split.back()[1];
        }
        else{
            vector<vector<int>> mappings;
            vector<int> subset;
            int curr=0;
            auto it = split.begin(); it++;
            while (it!=split.end()){
                if (*it=="|"){
                    mappings.push_back(subset);
                    subset.clear();
                }
                else{
                    subset.push_back(stoi(*it));
                }
                it++;
            }
            mappings.push_back(subset);
            rules[stoi(split.front().substr(0,split.front().length()-1))] = mappings;
        }
    }


    vector<string> valid42 = findValid(42,rules,pureRules);
    vector<string> valid31 = findValid(31,rules,pureRules);
    vector<string> valid = findValid(0,rules,pureRules);

    long sum=0;
    long sum2=0;
    for (auto it=toCheck.begin();it!=toCheck.end();it++){
        if (find(valid.begin(),valid.end(),*it)!=valid.end()){ sum++; sum2++; }
        else if ((*it).length()>24){
            string s = *it;
            vector<string> subsets;
            for (int i=0;i<s.length();i+=8){
                subsets.push_back(s.substr(i,8));
            }
            int curr = 42;
            int num42=0,num31=0, overlap=0;
            bool add=true;
            for (int i=0;i<subsets.size();i++){
                if (curr==42){
                    if (find(valid42.begin(),valid42.end(),subsets.at(i))==valid42.end()){ curr=31; }
                    else{ num42++; }
                }
                if (curr==31){
                    if (find(valid31.begin(),valid31.end(),subsets.at(i))==valid31.end()){ add=false; break; }
                    else{ num31++; }
                }
            }
            if (add==true && num31>0 && num42>0){
                if (num42>=num31+1){
                    sum2++;
                }
            }
        }
    }

    cout << sum << endl;
    cout << sum2 << endl;

}