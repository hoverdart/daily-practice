#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
int longestDistinctWindow(const vector<int>&, int);
int main(){
 assert(longestDistinctWindow({1,2,1,2,3},2)==4);
 assert(longestDistinctWindow({4,4,4},1)==3);
 assert(longestDistinctWindow({1,2,3},1)==1);
 assert(longestDistinctWindow({},3)==0);
 assert(longestDistinctWindow({1,2},0)==0);
 assert(longestDistinctWindow({1,2,2,1,3,3,2},2)==4);
 cout<<"easy tests passed\n";
}
