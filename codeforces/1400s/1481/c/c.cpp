#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> a(n), b(n), c(m);
  for (auto& i: a) cin >> i;
  for (auto& i: b) cin >> i;
  for (auto& i: c) cin >> i;
  map<int,vector<int>> unsat;
  map<int,vector<int>> sat;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) unsat[b[i]].push_back(i);
    else sat[b[i]].push_back(i);
  }
  vector<int> ans(m);
  int idx = -1; //safe index to paint over
  for (int i = m-1; i >= 0; i--) {
    if (!unsat[c[i]].empty()) {
      ans[i] = unsat[c[i]].back();
      idx = ans[i];
      unsat[c[i]].pop_back();
    }
    else if (!sat[c[i]].empty()) {
      ans[i] = sat[c[i]].back();
      idx = ans[i];
    }
    else if (idx != -1) ans[i] = idx;
    else {
      cout << "NO\n";
      return;
    }
  }
  bool poss = true;
  for (auto p: unsat) if (!p.second.empty()) poss = false;
  if (!poss) {
    cout << "NO\n";
  }
  else {
    cout << "YES\n";
    for (int i = 0; i < m; i++) {
      cout << ans[i]+1 << " \n"[i==m-1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
