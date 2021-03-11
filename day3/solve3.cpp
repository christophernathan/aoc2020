#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream file;
    file.open("input3.txt");
    string map[323];
    int i=0;
    while (file >> map[i++]);

    pair <int, int> params[5] = {make_pair(1,1), make_pair(3,1), make_pair(5,1), make_pair(7,1), make_pair(1,2)};
    long long final = 1;
    for (int i=0;i<5;i++){
        int row = params[i].second, col = params[i].first, tally = 0;
        while (row<323){
            if (map[row][col%31] == '#'){ tally++; }
            row+=params[i].second, col+=params[i].first;
        }
        final*=tally;
    }
    cout << final << endl;
}