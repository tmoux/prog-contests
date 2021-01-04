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
  cout << S.size() << '\n';
}
