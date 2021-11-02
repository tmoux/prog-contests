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

const int maxn = 55;

int N;
vector<int> adj[maxn];
int C[maxn];
int depth[maxn];
int par[maxn];

void dfs(int i, int p) {
  par[i] = p;
  C[i] += C[p];
  depth[i] = depth[p] + 1;
  for (int j: adj[i]) if (j != p) {
    dfs(j, i);
  }
}

int lca(int a, int b) {
  while (depth[a] > depth[b]) a = par[a];
  while (depth[b] > depth[a]) b = par[b];
  while (a != b) {
    a = par[a];
    b = par[b];
  }
  return a;
}

int solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) {
    adj[i].clear();
    depth[i] = 0;
    par[i] = 0;
    cin >> C[i];
  }
  for (int i = 0; i < N-1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 0);
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ckmax(ans, C[i]);
    for (int j = 1; j <= N; j++) {
      if (lca(i,j) == 1) {
        ckmax(ans, C[i] + C[j] - C[1]);
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
