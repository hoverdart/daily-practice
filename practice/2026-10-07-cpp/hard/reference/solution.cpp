#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;
int longestStableSignal(const vector<int>& signal,int k,int limit){
 if(k<=0) return 0;
 unordered_map<int,int> freq; deque<int> minQ,maxQ; int left=0,best=0;
 for(int right=0;right<(int)signal.size();++right){
  int x=signal[right]; ++freq[x];
  while(!minQ.empty()&&signal[minQ.back()]>x) minQ.pop_back(); minQ.push_back(right);
  while(!maxQ.empty()&&signal[maxQ.back()]<x) maxQ.pop_back(); maxQ.push_back(right);
  while((int)freq.size()>k||(long long)signal[maxQ.front()]-signal[minQ.front()]>limit){
   int leaving=signal[left]; if(--freq[leaving]==0) freq.erase(leaving);
   if(minQ.front()==left) minQ.pop_front(); if(maxQ.front()==left) maxQ.pop_front(); ++left;
  }
  best=max(best,right-left+1);
 }
 return best;
}
