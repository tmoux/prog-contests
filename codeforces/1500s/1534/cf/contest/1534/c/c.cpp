#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int M = 1e9+7;

void dfs(int i, vector<bool>& visited, const vector<vector<int>>& adj) {
  visited[i] = true;
  for (int j: adj[i]) {
    if (!visited[j]) dfs(j, visited, adj);
  }
}

void solve() {
  int n; cin >> n;
  vector<int> pos(n);
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    x--;
    pos[x] = i;
  }
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    x--;
    adj[i].push_back(pos[x]);
    adj[pos[x]].push_back(i);
  }
  vector<bool> visited(n, false);

  int ans = 1;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i, visited, adj);
      ans = (2 * ans) % M;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

