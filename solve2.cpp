#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream file;
    file.open("input2.txt");
    pair <pair <string, string>, string> input[1000];
    int i=0;
    string a;
    string b;
    string c;
    while (file >> a){
        file >> b >> c;
        input[i].first.first=a, input[i].first.second=b, input[i++].second=c;
    }
    pair <string, string> params[1000];
    char letter[1000];
    for (int i=0;i<1000;i++){
        string str = input[i].first.first;
        letter[i] = (input[i].first.second)[0];
        for (int a=0;a<str.size();a++){
            if (str[a]=='-'){
                params[i].first = str.substr(0,a);
                params[i].second = str.substr(a+1, str.size()-a-1);
                break;
            }
        }
    }

    int final=0;
    for (int i=0;i<1000;i++){
        string str = input[i].second;
        int tally=0;
        if (str[stoi(params[i].first)-1]==letter[i]){ tally++; }
        if (str[stoi(params[i].second)-1]==letter[i]){ tally++; }
        if (tally%2 == 1){ final++; }
    }
    cout << final << endl;
}