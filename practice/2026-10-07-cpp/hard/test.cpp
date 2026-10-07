#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
int longestStableSignal(const vector<int>&,int,int);
int main(){
 assert(longestStableSignal({1,3,2,2,5},3,2)==4);
 assert(longestStableSignal({8,2,4,7},4,4)==2);
 assert(longestStableSignal({4,4,4},1,0)==3);
 assert(longestStableSignal({},2,3)==0);
 assert(longestStableSignal({1,2,1,3,2,2},2,10)==3);
 assert(longestStableSignal({10,1,2,3,4,5},10,3)==4);
 assert(longestStableSignal({1,1},0,100)==0);
 cout<<"hard tests passed\n";
}
