#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) begin(x),end(x)
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

const int maxn = 2e5+5;
map<int,int> adj[maxn];
int cnt[26][26];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  while (m--) {
    char c; cin >> c;
    if (c == '+') {
      int u, v; char C;
      cin >> u >> v >> C;
      int cc = C-'a';
      adj[u][v] = cc;
      if (adj[v].count(u)) {
        int x = min(adj[u][v],adj[v][u]);
        int y = max(adj[u][v],adj[v][u]);
        cnt[x][y]++;
      }
    }
    else if (c == '-') {
      int u, v; cin >> u >> v;
      if (adj[v].count(u)) {
        int x = min(adj[u][v],adj[v][u]);
        int y = max(adj[u][v],adj[v][u]);
        cnt[x][y]--;
      }
      adj[u].erase(v);
    }
    else if (c == '?') {
      int k; cin >> k;
      bool poss = false;
      if (k % 2 == 0) {
        for (int i = 0; i < 26; i++) {
          poss |= cnt[i][i];
        }
      }
      else {
        for (int i = 0; i < 26; i++) {
          for (int j = i; j < 26; j++) {
            poss |= cnt[i][j];
          }
        }
      }
      cout << (poss?"YES":"NO") << '\n';
    }
  }
}
