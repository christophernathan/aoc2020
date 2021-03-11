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

int main(){
    long cardPublic = 10604480;
    long doorPublic = 4126658;
    long subject = 7;
    long value = 1;
    long i=0;
    while (value!=cardPublic){
        value*=subject;
        value = value%20201227;
        i++;
    }
    long cardLoop = i;
    value = 1;
    i=0;
    while (value!=doorPublic){
        value*=subject;
        value = value%20201227;
        i++;
    }
    long doorLoop = i;
    cout << cardLoop << " " << doorLoop << endl;

    subject = doorPublic;
    value=1;
    for (int i=0;i<cardLoop;i++){
        value*=subject;
        value = value%20201227;
    }
    cout << value << endl;
}