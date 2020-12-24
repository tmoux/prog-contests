#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];
int k;
bool flag;

int dfs(int i, int p, int d) {
  vector<int> v, u;
  for (int j: adj[i]) if (j != p) {
    int x = dfs(j,i,d+1);
    if (x-d+1 > k) {
      u.push_back(x);
    }
    else {
      v.push_back(x);
    }
  }
  if (v.empty() && u.empty()) return d;
  else {
    if (u.size() >= 2) {
      flag = false;
      return n;
    }
    else if (u.size() == 1) {
      return u[0];
    }
    else {
      sort(v.begin(),v.end());
      return v[0];
    }
  }
  return n;
}

bool check(int x) {
  k = x;
  flag = true;
  if (dfs(0,0,0) > k) flag = false;
  return flag;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) adj[i].clear();
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    --u; --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int lo = 0, hi = n-1;
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    if (check(mid)) {
      hi = mid;
    }
    else {
      lo = mid;
    }
  }
  cout << hi << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
