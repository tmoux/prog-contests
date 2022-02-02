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

struct Edge {
  int u, v, w;
  bool operator<(const Edge& rhs) const {
    return w < rhs.w;
  }
};

struct DSU {/*{{{*/
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};/*}}}*/

struct EdgeTracker {
  int n;
  deque<Edge> left, right; 
  ll curMST;
  ll curLeft, curRight;
  int nextInc;
  ll incSinceRebuild;

  EdgeTracker(const vector<Edge>& edges, int n_) : n(n_) {
    for (auto e: edges) right.push_back(e);
    rebuild();
  }

  // recalc curMST, curLeft, curRight, nextInc, incSinceRebuild
  void rebuild() {
    curMST = 0;
    incSinceRebuild = 0;  
    curLeft = curRight = 0;
    DSU dsu(n);
    for (int i = 0, j = 0; i < sz(left) || j < sz(right);) {
      if (i < sz(left) && (j >= sz(right) || left[i] < right[j])) {
        auto [u, v, w] = left[i];
        if (dsu.Union(u, v)) {
          curMST += w;
          curLeft++;
        }
        i++;
      }
      else {
        auto [u, v, w] = right[j];
        if (dsu.Union(u, v)) {
          curMST += w;
          curRight++;
        }
        j++;
      }
    }

    nextInc = right.empty() ? 1e9 : right.front().w;
    for (int i = 0, j = 0; i < sz(left); i++) {
      while (j < sz(right) && right[j] < left[i]) j++;
      if (j < sz(right)) {
        int d = right[j].w - left[i].w;
        ckmin(nextInc, (d+1)/2);
      }
    }
  }

  // inc is how much the current query has increased
  ll query(int inc) {
    if (inc < nextInc) {
      nextInc -= inc;
      incSinceRebuild += inc;
    }
    else { // rebuild
      int delta = incSinceRebuild + inc;
      for (auto& [v, u, w]: left) w += delta;
      while (!right.empty() && right.front().w <= delta) {
        auto [v, u, w] = right.front(); right.pop_front();
        left.push_front({v, u, abs(w-delta)});
      }
      for (auto& [v, u, w]: right) w -= delta;
      rebuild();
    }
    return curMST + incSinceRebuild * (curLeft - curRight);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<Edge> edges;
  REP(m) {
    int u, v, w; cin >> u >> v >> w;
    edges.push_back({u,v,w});
  }
  sort(all(edges));
  int P; cin >> P;
  int k, a, b, c; cin >> k >> a >> b >> c;
  vector<int> queries(k);
  F0R(i, P) cin >> queries[i];
  FOR(i, P, k) queries[i] = (1LL * queries[i-1] * a + b) % c;

  sort(all(queries));
  EdgeTracker tracker(edges, n);

  ll ans = 0;
  for (int i = 0; i < k; i++) {
    int d = i == 0 ? queries[i] : queries[i] - queries[i-1];
    ans ^= tracker.query(d);
  }
  cout << ans << '\n';
}
