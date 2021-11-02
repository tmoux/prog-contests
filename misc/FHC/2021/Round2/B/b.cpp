#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
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

const int maxn = 8e5+5;
const int maxk = 20;

int N;
vector<int> adj[maxn];
int depth[maxn];
int par[maxk][maxn];
int F[maxn];
int tin[maxn];
int pt = 0;
int pfx[maxn];

void dfs(int i, int p) {
  tin[i] = pt++;
  depth[i] = depth[p] + 1;
  par[0][i] = p;
  FOR(k, 1, maxk) {
    par[k][i] = par[k-1][par[k-1][i]];
  }
  for (int j: adj[i]) if (j != p) {
    dfs(j, i);
  }
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) swap(a,b);
  for (int k = maxk - 1; k >= 0; k--) {
    int bb = par[k][b];
    if (bb != -1 && depth[bb] >= depth[a])
      b = bb;
  }
  if (a == b) return a;
  for (int k = maxk - 1; k >= 0; k--) {
    int aa = par[k][a];
    int bb = par[k][b];
    if (aa != bb) {
      a = aa;
      b = bb;
    }
  }
  return par[0][a];
}

int dfs2(int i, int p, int& ans) {
  for (int j: adj[i]) if (j != p) {
    pfx[i] += dfs2(j, i, ans);
  }
  if (i != 1 && pfx[i] == 0) ans++;
  return pfx[i];
}

int solve() {
  cin >> N;
  pt = 0;
  FOR(i, 1, N+1) {
    adj[i].clear();
    pfx[i] = 0;
  }
  F0R(i, maxk) {
    FOR(j, 0, N+1) {
      par[i][j] = -1;
    }
  }
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 0);

  map<int,vector<int>> fs;
  FOR(i, 1, N+1) {
    cin >> F[i];
    fs[F[i]].push_back(i);
  }
  for (auto& p: fs) {
    auto& v = p.second;
    sort(all(v), [](int a, int b) {
        return tin[a] < tin[b];
        });
    for (int i = 0; i < ((int)v.size())-1; i++) {
      int a = v[i];
      int b = v[i+1];
      int lc = lca(a, b);
      if (a != lc) {
        pfx[a]++;
        pfx[lc]--;
      }
      if (b != lc) {
        pfx[b]++;
        pfx[lc]--;
      }
    }
  }

  int ans = 0;
  dfs2(1, 0, ans);

  /*
  FOR(i, 1, N+1) {
    cout << i << ": " << pfx[i] << endl;
  }
  */

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
