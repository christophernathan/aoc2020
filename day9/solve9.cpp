#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

list<int> nums;
vector<int> contiguous; 

bool valid(int n){
    for (int a : nums) {
        for (int b : nums){
            if (a+b==n && a!=b){ return true; }
        }
    }
    return false;
}

int sumOfRange(int n){
    int currStart = 0;
    int sum = 0;
    for (int a=0; a<contiguous.size(); a++){
        sum+=contiguous.at(a);
        if (sum == n){
            int smallest = contiguous.at(currStart);
            int largest = contiguous.at(currStart);
            for (int b=currStart+1; b<=a; b++){
                if (contiguous.at(b)>largest){ largest=contiguous.at(b); }
                if (contiguous.at(b)<smallest){ smallest=contiguous.at(b); }
            }
            return smallest+largest;
        }
        else if (sum > n){
            currStart++;
            a=currStart-1;
            sum=0;
        }
    }
    return 0;
}

int main(){
    ifstream file;
    file.open("input9.txt");
    int next;
    for (int i=0; i<25; i++){
        file >> next;
        nums.push_back(next);
        contiguous.push_back(next);
    } 
    while (file >> next){
        if (valid(next)){
            nums.push_back(next);
            contiguous.push_back(next);
            nums.pop_front();
        }
        else{
            cout << next << endl;
            break;
        }
    }
    cout << sumOfRange(next) << endl;
    return 0;
}