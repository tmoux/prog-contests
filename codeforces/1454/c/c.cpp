#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    map<int,vector<int>> mp;
    for (int i = 0; i < n; i++) {
      int ai; cin >> ai;
      mp[ai].push_back(i);
    }
    int ans = n;
    for (auto p: mp) {
      auto& v = p.second;
      int prev = -1;
      int spaces = 0;
      for (auto i: v) {
        if (i > prev+1) spaces++;
        prev = i;
      }
      if (v.back() != n-1) spaces++;
      ans = min(ans,spaces);
    }
    cout << ans << '\n';
  }
}

