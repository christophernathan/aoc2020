#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream file;
    int nums[200];
    file.open("input1.txt");
    int i=0;
    while (file >> nums[i++]);
    for (int a=0; a<200; a++){
        for (int b=0;b<200;b++){
            for (int c=0;c<200;c++){
                if (a!=b && b!=c && a!=c && nums[a]+nums[b]+nums[c]==2020){
                    cout << nums[a]*nums[b]*nums[c] << endl;
                }
            }
        }
    }
}