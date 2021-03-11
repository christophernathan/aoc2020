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

bool compare(string a, string b) {return a<b;}

void add(vector<string> &currList, string s){
    if (find(currList.begin(),currList.end(),s)==currList.end()){ currList.push_back(s); }
}

void findIntersection(vector<string> &newIngredients, vector<string> &currentMapping){
    auto it = currentMapping.begin();
    while (it!=currentMapping.end()){
        if (find(newIngredients.begin(),newIngredients.end(),*it)==newIngredients.end()){ currentMapping.erase(it); }
        else{ it++; }
    }
}

bool isBijective(map<string,vector<string>> &mappings){
    for (auto it=mappings.begin();it!=mappings.end();it++){
        if (it->second.size()!=1){ return false; }
    }
    return true;
}

void establishMapping(map<string,vector<string>> &mappings){
    for (auto it=mappings.begin();it!=mappings.end();it++){
        if (it->second.size()==1){ 
            for (auto rest=mappings.begin();rest!=mappings.end();rest++){
               auto existsElsewhere = find(rest->second.begin(),rest->second.end(),it->second.front());
               if (rest!=it && existsElsewhere!=rest->second.end()){
                   rest->second.erase(existsElsewhere);
               }
            }
        }
    }
}

void simplifyMapping(map<string,vector<string>> &mappings){
    while (!isBijective(mappings)){
        establishMapping(mappings);
    }
}

int main(){
    ifstream file;
    file.open("input21.txt");

    vector<pair<vector<string>,vector<string>>> foods;
    vector<string> allIngredients;
    vector<string> allAllergens;

    string s;
    vector<string> newIngredients;
    while (file >> s){
        if (s[0]=='('){
            vector<string> newAllergens;
            while (file >> s){
                if (s[s.length()-1]==')'){
                    newAllergens.push_back(s.substr(0,s.length()-1));
                    add(allAllergens,s.substr(0,s.length()-1));
                    break;
                }
                else{
                    newAllergens.push_back(s.substr(0,s.length()-1));
                    add(allAllergens,s.substr(0,s.length()-1));
                }
            }
            foods.push_back(make_pair(newIngredients,newAllergens));
            newIngredients.clear();
        }
        else{
            newIngredients.push_back(s);
            add(allIngredients,s);
        }
    }

    map<string,vector<string>> allergenMappings;
    for (pair<vector<string>,vector<string>> p : foods){
        for (string allergen : p.second){
            if (allergenMappings.find(allergen)==allergenMappings.end()){
                allergenMappings.insert({allergen,p.first});
            }
            else{
                findIntersection(p.first,allergenMappings[allergen]);
            }
        }
    }

    simplifyMapping(allergenMappings);

    vector<string> deadlyIngredients;
    for (auto it=allergenMappings.begin();it!=allergenMappings.end();it++){
        deadlyIngredients.push_back(it->second.front());
    }

    long sum=0;
    for (pair<vector<string>,vector<string>> p : foods){
        for (string ingredient : p.first){
            if (find(deadlyIngredients.begin(),deadlyIngredients.end(),ingredient)==deadlyIngredients.end()){
                sum++;
            }
        }
    }
    cout << sum << endl;

    for (auto it=allergenMappings.begin(); it!=allergenMappings.end();it++){
        cout << it->second.front() << ",";
    } cout << endl;
}
