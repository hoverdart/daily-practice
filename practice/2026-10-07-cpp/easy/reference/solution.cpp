#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
int longestDistinctWindow(const vector<int>& readings, int k) {
 if(k<=0) return 0;
 unordered_map<int,int> freq;
 int left=0,best=0;
 for(int right=0; right<(int)readings.size(); ++right){
  ++freq[readings[right]];
  while((int)freq.size()>k){ int x=readings[left++]; if(--freq[x]==0) freq.erase(x); }
  best=max(best,right-left+1);
 }
 return best;
}
