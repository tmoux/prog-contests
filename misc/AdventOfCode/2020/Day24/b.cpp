#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<string,pair<int,int>> mp = {
  {"e",{1,0}},
  {"w",{-1,0}},
  {"se",{0,-1}},
  {"nw",{0,1}},
  {"sw",{-1,-1}},
  {"ne",{1,1}}
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  set<pair<int,int>> S;
  string s;
  while (getline(cin,s)) {
    int x = 0, y = 0;
    string cur = "";    
    for (char c: s) {
      cur += c;
      if (mp.count(cur)) {
        x += mp[cur].first;
        y += mp[cur].second;
        cout << cur << '\n';
        cout << x << ' ' << y << '\n';
        cur.clear();
      }
    }
    cout << x << ' ' << y << '\n';
    if (S.count({x,y})) {
      S.erase({x,y});
    }
    else {
      S.insert({x,y});
    }
  }
  for (int i = 0; i < 100; i++) {
    map<pair<int,int>,int> mp;
    set<pair<int,int>> ns;
    for (auto p: S) {
      int x = p.first, y = p.second;
      int cnt = 0;
      cnt += S.count({x+1,y});
      cnt += S.count({x-1,y});
      cnt += S.count({x,y-1});
      cnt += S.count({x,y+1});
      cnt += S.count({x+1,y+1});
      cnt += S.count({x-1,y-1});
      if (cnt == 0 || cnt > 2) {

      }
      else {
        ns.insert({x,y});
      }
      mp[make_pair(x+1,y)]++;
      mp[make_pair(x-1,y)]++;
      mp[make_pair(x,y-1)]++;
      mp[make_pair(x,y+1)]++;
      mp[make_pair(x+1,y+1)]++;
      mp[make_pair(x-1,y-1)]++;
    }
    for (auto p: mp) {
      if (!S.count(p.first) && p.second == 2) {
        ns.insert(p.first);
      }
    }
    S = ns;
    cout << i << ": " << S.size() << '\n';
  }
}
