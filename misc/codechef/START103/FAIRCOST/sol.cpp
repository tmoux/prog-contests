#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

// Precompute cost of each edge (that is a bridge).
// Binary search on answer (x).
//

using vi = vector<int>;
using pii = pair<int, int>;

struct BC {
  vi num, st;
  vector<vector<pii>> ed;
  vector<array<int, 3>> edges;
  vector<int> sub_size;
  vector<pair<array<int, 3>, ll>> bridges; // {id, u, v}, cost
  int Time;

  int N;

  BC(int _N, int M) : N(_N) {
    sub_size.resize(N);
    ed.resize(N);
    edges.resize(M);
  }
  template<class F>
  int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, e, y, top = me;
    sub_size[at] = 1;
    for (auto pa : ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
          top = min(top, num[y]);
          if (num[y] < me)
            st.push_back(e);
        } else {
          int si = sz(st);
          int up = dfs(y, e, f);
          sub_size[at] += sub_size[y];
          top = min(top, up);
          if (up == me) { // BCC (list of edges)
            st.push_back(e);
            // f(vi(st.begin() + si, st.end()));
            st.resize(si);
          }
          else if (up < me) st.push_back(e);
          else { // BRIDGE
            // auto [a, b, id] = edges[e];
            ll cost = 1LL * sub_size[y] * (N - sub_size[y]) * edges[e][2];
            bridges.push_back({{e, at, y}, cost});
          }
        }
      }
    return top;
  }

  template<class F>
  void bicomps(F f) {
    num.assign(sz(ed), 0);
    FOR(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
  }
};

ll solve() {
  int N, M; cin >> N >> M;
  BC bc(N, M);
  F0R(i, M) {
    int u, v, w; cin >> u >> v >> w;
    u--, v--;
    bc.edges[i] = {u, v, w};
    bc.ed[u].push_back({v, i});
    bc.ed[v].push_back({u, i});
  }

  bc.bicomps([&]{});

  auto check = [&](ll x) -> bool { // all must be <= x
    vector<ll> C(N, 0);
    for (auto [xx, cost]: bc.bridges) {
      auto [id, a, b] = xx;
      ll take = min(cost, x - C[b]);
      C[b] += take;
      C[a] += cost - take;
      if (C[a] > x) return false;
    }
    F0R(i, N) if (C[i] > x) return false;
    return true;
  };

  ll lo = -1, hi = 1e18;
  while (lo + 1 < hi) {
    ll mid = (lo + hi) / 2;
    (check(mid) ? hi : lo) = mid;
  }
  return hi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 1;
  while (T--) cout << solve() << '\n';
}
