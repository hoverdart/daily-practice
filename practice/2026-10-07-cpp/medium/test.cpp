#include <cassert>
#include <iostream>
#include <vector>
#include <array>
using namespace std;
long long fastestRoute(int,const vector<array<int,3>>&);
int main(){
 assert(fastestRoute(4,{{0,1,5},{1,3,4},{0,2,2},{2,3,10}})==9);
 assert(fastestRoute(3,{{0,1,7}})==-1);
 assert(fastestRoute(1,{})==0);
 assert(fastestRoute(5,{{0,1,10},{0,2,3},{2,1,1},{1,3,2},{2,3,8},{3,4,2}})==8);
 assert(fastestRoute(3,{{0,1,0},{1,2,0},{0,2,5}})==0);
 cout<<"medium tests passed\n";
}
