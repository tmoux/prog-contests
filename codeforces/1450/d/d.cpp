#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> maxx(n+1,0), dup(n+1,0);
    map<int,vector<int>> mp;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      mp[a[i]].push_back(i);
    }
    set<int> s = {-1,n};
    for (auto p: mp) {
      int i = p.first;
      auto v = p.second;
      int mx = 0;
      int mx_dup = 0;

      map<pair<int,int>,vector<int>> ranges;
      for (auto j: v) {
        auto lo = prev(s.lower_bound(j));
        auto hi = s.upper_bound(j);
        mx = max(mx,*hi-1-*lo);
        ranges[make_pair(*lo+1,*hi-1)].push_back(j);
      }

      for (auto p: ranges) {
        auto pp = p.first;
        auto vv = p.second;
        if (vv.size() == 1 && (vv[0] == pp.first || vv[0] == pp.second)) {}
        else {
          mx_dup = max(mx_dup,pp.second-pp.first);
        }
      }
      vector<int> r;
      for (auto p: ranges) {
        auto pp = p.first;
        r.push_back(pp.second-pp.first+1);
      }
      sort(r.begin(),r.end());
      if (r.size() > 1) {
        mx_dup = max(mx_dup,r[r.size()-2]);
      }

      maxx[mx] = max(maxx[mx],i);
      dup[1] |= v.size() >= 2;
      if (mx_dup > 1) dup[mx_dup] = 1;

      for (auto j: v) {
        s.insert(j);
      }
    }
    
    for (int i = n-1; i >= 1; i--) {
      maxx[i] = max(maxx[i],maxx[i+1]);
    }
    for (int i = n-1; i >= 2; i--) {
      dup[i] = max(dup[i],dup[i+1]);
    }
    for (int i = 1; i <= n; i++) {
      //cout << i << ": " << maxx[i] << ' ' << dup[i] << endl;
      if (maxx[i] == n+1-i && dup[i] == 0) {
        cout << 1;
      }
      else {
        cout << 0;
      }
    }
    cout << '\n';
  }
}
