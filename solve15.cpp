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

void findSolution(vector<int> nums, int toStop){
    map<int,uint64_t>cache;
    for (int i=0;i<nums.size()-1;i++){
        cache[nums[i]]=i;
    }
    nums.reserve(toStop);
    while (true){
        int onTop = nums.back();
        auto it = cache.find(onTop);
        if (it == cache.end()){
            nums.push_back(0);
        }
        else{
            int dist = nums.size()-1-it->second;
            nums.push_back(dist);
        }
        cache[onTop] = nums.size()-2;
        if (nums.size() == toStop){
            cout << nums.back() << endl;
            return;
        }
    }
}

int main(){
    vector<int> nums = {0,6,1,7,2,19,20};
    findSolution(nums,2020);
    findSolution(nums,30000000);
}