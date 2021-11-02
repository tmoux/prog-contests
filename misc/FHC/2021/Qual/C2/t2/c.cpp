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

int dp[maxn][maxn][2]; //node, num paths, whether continuing current path

int calcdp[maxn][maxn];


int calc(int i, int p, int k);
int f(int i, int p, int k, int v);

int calc(int i, int p, int k) {
  memset(calcdp, 0, sizeof calcdp);

  for (int j = 1; j <= N; j++) {
    for (int tunnels = 0; tunnels <= k; tunnels++) {
      calcdp[j][tunnels] = calcdp[j-1][tunnels];
    }
    if (adj[i][j] && j != p) {
      for (int tunnels = 0; tunnels <= k; tunnels++) {
        for (int use = 0; tunnels + use <= k; tunnels++) {
          ckmax(calcdp[j][tunnels+use], calcdp[j-1][tunnels] + f(j, i, use, 0));
        }
      }
    }
  }
  return calcdp[N][k];
}

int f(int i, int p, int k, int v) {
  int& res = dp[i][k][v];
  if (res != -1) return res;

  res = 0;

  if (v == 0) { //no current path
    //ignore this node
    ckmax(res, calc(i, p, k));
    if (k > 0) {
      //choose one node to start a path
      for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
        adj[i][j] = false;
        for (int use = 0; use+1 <= k; use++) {
          int path = C[i] + f(j, i, use, 1);
          ckmax(res, path + calc(i, p, k-use-1));
        }
        adj[i][j] = true;
      }

      //choose two nodes to make a path
      for (int j1 = 1; j1 <= N; j1++) if (adj[i][j1] && j1 != p) {
        for (int j2 = 1; j2 <= N; j2++) if (adj[i][j2] && j2 != p && j1 != j2) {
          adj[i][j1] = false;
          adj[i][j2] = false;
          for (int use1 = 0; use1+1 <= k; use1++) {
            for (int use2 = 0; use1+use2+1 <= k; use2++) {
              int path = C[i] + f(j1, i, use1, 1) + f(j2, i, use2, 1);
              ckmax(res, path + calc(i, p, k-use1-use2-1));
            }
          }
          adj[i][j1] = true;
          adj[i][j2] = true;
        }
      }
    }
  }
  else { //current path
    ckmax(res, C[i] + calc(i, p, k));
    //pick a child to continue to path
    for (int j = 1; j <= N; j++) if (adj[i][j] && j != p) {
      adj[i][j] = false;
      for (int use = 0; use <= k; use++) {
        int path = C[i] + f(j, i, use, 1);
        ckmax(res, path + calc(i, p, k-use));
      }
      adj[i][j] = true;
    }
  }
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

  K++;

  int ans = 0;
  //try 0
  if (K >= 2) {
    memset(dp, -1, sizeof dp);
    ckmax(ans, f(1, 1, K-2, 0));
  }

  //try 1
  for (int i = 1; i <= N; i++) {
    if (adj[1][i]) {
      adj[1][i] = false;
      memset(dp, -1, sizeof dp);
      for (int use = 0; use+1 <= K; use++) {
        int tr = C[1] + f(i, 1, use, 1) + f(1, 1, K-use-1, 0);
        if (i == 2 && use == 0) {
          DEBUG(C[1] + f(i,1,use,1));
          DEBUG(K-use-1);
          DEBUG(f(1, 1, K-use-1, 0));
        }
        ckmax(ans, tr);
      }
      adj[1][i] = true;
    }
  }

  //try 2
  for (int i = 1; i <= N; i++) if (adj[1][i]) {
    for (int j = 1; j <= N; j++) if (adj[1][j] && i != j) {
      adj[1][i] = false;
      adj[1][j] = false;
      memset(dp, -1, sizeof dp);
      for (int use1 = 0; use1 <= K; use1++) {
        for (int use2 = 0; use1+use2+2 <= K; use2++) {
          int tr = C[1] + f(i, 1, use1, 1) + f(j, 1, use2, 1) + f(1, 1, K-use1-use2-2, 0);
          //ckmax(ans, tr);
        }
      }
      adj[1][i] = true;
      adj[1][j] = true;
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
