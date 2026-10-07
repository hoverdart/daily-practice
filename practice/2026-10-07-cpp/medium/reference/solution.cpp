#include <vector>
#include <array>
#include <queue>
#include <utility>
#include <functional>
#include <limits>
using namespace std;
long long fastestRoute(int n,const vector<array<int,3>>& roads){
 vector<vector<pair<int,int>>> g(n);
 for(auto e:roads){auto [u,v,w]=e; g[u].push_back({v,w}); g[v].push_back({u,w});}
 const long long INF=numeric_limits<long long>::max()/4;
 vector<long long> dist(n,INF); using State=pair<long long,int>;
 priority_queue<State,vector<State>,greater<State>> pq;
 dist[0]=0; pq.push({0,0});
 while(!pq.empty()){
  auto [d,u]=pq.top(); pq.pop(); if(d!=dist[u]) continue; if(u==n-1) return d;
  for(auto [v,w]:g[u]){long long nd=d+(long long)w; if(nd<dist[v]){dist[v]=nd; pq.push({nd,v});}}
 }
 return -1;
}
