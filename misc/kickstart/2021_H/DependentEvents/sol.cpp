#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std
// }}}

const int M = 1e9+7;
int madd(int a, int b) {
  a += b;
  if (a >= M) a -= M;
  return a;
}
int msub(int a, int b) {
  return madd(a, M-b);
}
int mult(int a, int b) {
  return (1LL*a*b) % M;
}
int modexp(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b&1) res = mult(res,a);
    a = mult(a,a);
      b >>= 1;
  }
  return res;
}
int inverse(int x) {
  return modexp(x,M-2);
}

vector<int> solve() {
  const int denom_1e6 = inverse(1000000);/*{{{*/
  int N, Q; cin >> N >> Q;
  int K; cin >> K;
  vector<int> prob(N); //probability of event i occuring
  vector<int> A(N), B(N);
  vector<vector<int>> adj(N);
  prob[0] = mult(K, denom_1e6);
  for (int i = 1; i < N; i++) {
    int pi; cin >> pi; pi--;
    adj[i].push_back(pi);
    adj[pi].push_back(i);

    cin >> A[i] >> B[i];
    A[i] = mult(A[i], denom_1e6);
    B[i] = mult(B[i], denom_1e6);
  }/*}}}*/
  // setup lca{{{
  const int maxk = 18;
  vector<vector<int>> par(maxk, vector<int>(N, -1));
  vector<int> depth(N);
  y_combinator([&](auto dfs, int i, int p, int d) -> void {
    depth[i] = d;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      if (par[k-1][i] == -1) par[k][i] = -1;
      else par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) dfs(j, i, d+1);
  })(0, -1, 0);/*}}}*/

  auto lca = [&](int a, int b) -> int {/*{{{*/
    if (depth[a] > depth[b]) swap(a, b);
    for (int k = maxk-1; k >= 0; k--) {
      int bb = par[k][b];
      if (bb != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      int bb = par[k][b];
      if (aa != bb) {
        a = aa;
        b = bb;
      }
    }
    return par[0][a];
  };/*}}}*/

  // DFS to calculate probabilities{{{
  y_combinator([&](auto dfs, int i, int p) -> void {
    if (i != 0) {
      prob[i] = madd(mult(A[i], prob[p]),
                     mult(B[i], msub(1, prob[p])));
    }
    for (int j: adj[i]) if (j != p) dfs(j, i);
  })(0, 0);/*}}}*/

  auto calc_path = [&](int lc, int u, int D) {/*{{{*/
    // calculate probability of u occuring when lc has probability D
    vector<int> path = {u};
    while (u != lc) {
      u = par[0][u];
      path.push_back(u);
    }
    reverse(all(path));
    vector<int> p(sz(path)); p[0] = D;
    for (int i = 1; i < sz(path); i++) {
      p[i] = madd(mult(msub(A[path[i]], B[path[i]]), p[i-1]),
                  B[path[i]]);
    }
    return p.back();
  };/*}}}*/

  // Setup binary lifting{{{
  vector<vector<int>> a_jump(maxk, vector<int>(N));
  vector<vector<int>> b_jump(maxk, vector<int>(N));
  y_combinator([&](auto dfs, int i, int p) -> void {
    a_jump[0][i] = msub(A[i], B[i]);
    b_jump[0][i] = B[i];
    for (int k = 1; k < maxk; k++) {
      if (par[k][i] != -1) {
        int a_j = a_jump[k-1][i];
        int b_j = b_jump[k-1][i];

        int a_i = a_jump[k-1][par[k-1][i]];
        int b_i = b_jump[k-1][par[k-1][i]];

        a_jump[k][i] = mult(a_j, a_i);
        b_jump[k][i] = madd(mult(a_j, b_i), b_j);

      }
    }
    for (int j: adj[i]) if (j != p) dfs(j, i);
  })(0, -1);/*}}}*/

  auto calc_path_fast = [&](int lc, int u, int D) {
    int a_j = 1, b_j = 0;
    for (int k = maxk-1; k >= 0; k--) {
      if (par[k][u] != -1 && depth[par[k][u]] >= depth[lc]) {
        int a_i = a_jump[k][u];
        int b_i = b_jump[k][u];

        u = par[k][u];

        int na_j = mult(a_j, a_i);
        int nb_j = madd(mult(a_j, b_i), b_j);

        a_j = na_j;
        b_j = nb_j;
      }
    }
    assert(u == lc);

    return madd(mult(a_j, D), b_j);
  };

  vector<int> ans;
  F0R(_, Q) {
    int u, v; cin >> u >> v;
    u--; v--;
    int lc = lca(u, v);

    int t = 0;
    // Suppose lc occurs:
    int prob_u_1 = calc_path_fast(lc, u, 1);
    int prob_v_1 = calc_path_fast(lc, v, 1);
    t = madd(t, mult(prob[lc], mult(prob_u_1, prob_v_1)));

    // Suppose lc doesn't occur:
    int prob_u_2 = calc_path_fast(lc, u, 0);
    int prob_v_2 = calc_path_fast(lc, v, 0);
    t = madd(t, mult(msub(1, prob[lc]), mult(prob_u_2, prob_v_2)));

    // assert(calc_path(lc, u, 1) == calc_path_fast(lc, u, 1));
    // assert(calc_path(lc, v, 1) == calc_path_fast(lc, v, 1));
    // assert(calc_path(lc, u, 0) == calc_path_fast(lc, u, 0));
    // assert(calc_path(lc, v, 0) == calc_path_fast(lc, v, 0));

    ans.push_back(t);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    auto v = solve();
    cout << "Case #" << tc << ": ";
    for (auto i: v) cout << i << ' ';
    cout << '\n';
  }
}
