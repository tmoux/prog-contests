#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<pair<int,int>> a;
  for (int i = 0; i < n; i++) {
    int ai; cin >> ai;
    a.push_back({ai,i});
  }
  sort(a.begin(),a.end());
  reverse(a.begin(),a.end());
  set<int> s;
  int ans = 0;
  for (auto p: a) {
    int i = p.second;
    auto it = s.lower_bound(i);
    if (it != s.begin()) ++ans;
    if (it != s.end()) ++ans;
    s.insert(i);
  }
  cout << ans << '\n';
}
