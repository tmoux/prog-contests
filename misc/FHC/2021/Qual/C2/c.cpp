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

const int maxn = 55;

int N, K, C[maxn];
bool adj[maxn][maxn];

int maxchain[maxn];

int dfs(int i, int p) {
  maxchain[i] = C[i];
  for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
    int d = dfs(j, i);
    ckmax(maxchain[i], d);
  }
  return maxchain[i];
}

int dp[maxn][maxn][2]; //node, num extra tunnels, any/must start at top

//v = 0 --> must start at node i
//v = 1 --> can start anywhere in subtree
int f(int i, int p, int k, int v) {
  int& res = dp[i][k][v];
  if (res != -1) return res;

  res = 0;

  auto calc2 = [&](int k) {
    vector<int> children;
    for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
      children.push_back(j);
    }
    int num_children = children.size();
    vector<vector<int>> dp2(num_children+1, vector<int>(k+1, 0));

    F0R(j, k+1) dp2[0][j] = C[i];
    for (int j = 0; j < num_children; j++) {
      int child = children[j];
      for (int tunnels = 0; tunnels <= k; tunnels++) {
        ckmax(dp2[j+1][tunnels], dp2[j][tunnels]);
      }
      for (int tunnels = 0; tunnels <= k; tunnels++) {
        for (int use = 0; tunnels + use + 1 <= k; use++) {
          ckmax(dp2[j+1][tunnels+use+1], dp2[j][tunnels] + f(child, i, use, 1));
        }
      }
    }
    return dp2[num_children][k];
  };

  auto calc = [&]() {
    int ans = 0;
    for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
      adj[i][j] = false;
      for (int use = 0; use <= k; use++) {
        int nextSubtree = f(j, i, use, 0);
        ckmax(ans, calc2(k-use) + nextSubtree);
      }
      adj[i][j] = true;
    }
    ckmax(ans, calc2(k));
    return ans;
  };

  if (v == 1) {
    for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
      ckmax(res, f(j, i, k, 1));
    }
    for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
      adj[i][j] = false;
      ckmax(res, calc() + maxchain[j]);
      adj[i][j] = true;
    }
  }
  ckmax(res, calc());

  //printf("[%d][%d][%d]: %d\n", i, k, v, res);
  return res;
}

int solve() {
  cin >> N >> K;
  memset(adj, 0, sizeof adj);
  for (int i = 1; i <= N; i++) {
    cin >> C[i];
  }
  for (int i = 0; i < N-1; i++) {
    int a, b; cin >> a >> b;
    adj[a][b] = true;
    adj[b][a] = true;
  }
  if (K == 0) return C[1];

  dfs(1, 1);

  memset(dp, -1, sizeof dp);
  int ans = f(1, 1, K-1, 0);
  for (int j = 1; j <= N; j++) if (adj[1][j]) {
    adj[1][j] = false;
    memset(dp, -1, sizeof dp);
    ckmax(ans, f(1, 1, K-1, 0) + maxchain[j]);
    adj[1][j] = true;
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
