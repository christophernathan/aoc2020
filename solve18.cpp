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

uint64_t toInt (string &s, int &index)
{
    uint64_t r = 0;
    while (index < s.length() && s[index] >= '0' && s[index] <= '9'){
        r = r * 10 + (s[index] - '0');
        index++;
    }
    return r;
}

void addParens (string &s, int &index){
    s.insert (index, "(");
    index++;
    int temp = index;
    int parenCount = 0;
    while (temp < s.length() && parenCount >= 0)
    {
        if (s[temp] == '('){ parenCount++; }
        else if (s[temp] == ')'){ parenCount--; }
        temp++;
    }
    s.insert (temp, ")");
}

uint64_t eval(string &s, int &index){
    uint64_t sum=0;
    int operation=0;
    while (index<s.length()){
        if (s[index]=='+'){
            operation=1; index++;
        }
        else if (s[index]=='*'){
            operation=2; index++;
        }
        else if (s[index]=='('){
            index++;
            uint64_t res = eval(s,index);
            switch(operation){
                case 0: sum = res; break;
                case 1: sum += res; break;
                case 2: sum *= res; break;
            }
            operation=0;
        }
        else if (s[index]>='0' && s[index]<='9'){
            uint64_t res = toInt(s,index);
            switch(operation){
                case 0: sum = res; break;
                case 1: sum += res; break;
                case 2: sum *= res; break;
            }
            operation=0;
        }
        else if (s[index]==')'){
            index++;
            return sum;
        }
        else{
            index++;
        }

    }
    return sum;
}

uint64_t eval2(string &s, int &index){
    uint64_t sum=0;
    int operation=0;
    while (index<s.length()){
        if (s[index]=='+'){
            operation=1; index++;
        }
        else if (s[index]=='*'){
            index++;
            addParens(s,index);
            uint64_t res = eval2(s,index);
            sum *= res;
            operation=0;
        }
        else if (s[index]=='('){
            index++;
            uint64_t res = eval2(s,index);
            switch(operation){
                case 0: sum = res; break;
                case 1: sum += res; break;
                case 2: sum *= res; break;
            }
            operation=0;
        }
        else if (s[index]>='0' && s[index]<='9'){
            uint64_t res = toInt(s,index);
            switch(operation){
                case 0: sum = res; break;
                case 1: sum += res; break;
                case 2: sum *= res; break;
            }
            operation=0;
        }
        else if (s[index]==')'){
            index++;
            return sum;
        }
        else{
            index++;
        }
    }
    return sum;
}

int main(){
    ifstream file;
    file.open("input18.txt");

    list<string> equation;

    string nextLine;
    uint64_t sum=0;
    while (getline(file,nextLine)){
        int index=0;
        uint64_t res = eval2(nextLine, index);
        cout << res << endl;
        sum+=res;
    }
    cout << sum << endl;
}