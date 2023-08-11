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

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

const int maxn = 1e6+6;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

vector<int> primes(int x) {
  vector<int> ps;
  while (x > 1) {
    int p = spf[x];
    ps.push_back(p);
    while (x % p == 0) x /= p;
  }
  return ps;
}

vector<int> P[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  init_spf();
  DSU dsu(maxn);
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    P[i] = primes(A[i]);
    F0R(idx, sz(P[i]) - 1) {
      dsu.Union(P[i][idx], P[i][idx+1]);
    }
  }
  set<pair<int, int>> edges;
  F0R(i, N) {
    const auto& pi = P[i];
    auto ps = primes(A[i] + 1);
    F0R(a, sz(ps)) {
      FOR(b, a+1, sz(ps)) {
        if (dsu.Find(ps[a]) == dsu.Find(ps[b])) continue;
        edges.insert({dsu.Find(ps[a]), dsu.Find(ps[b])});
      }
    }
    for (auto a: pi) {
      for (auto b: ps) {
        if (dsu.Find(a) == dsu.Find(b)) continue;
        edges.insert({dsu.Find(a), dsu.Find(b)});
      }
    }
  }

  auto query = [&](int s, int t) -> int {
    const auto& ps = P[s];
    const auto& pt = P[t];
    for (auto p: ps) {
      for (auto q: pt) {
        if (dsu.Find(p) == dsu.Find(q)) {
          return 0;
        }
      }
    }
    for (auto p: ps) {
      for (auto q: pt) {
        int x = dsu.Find(p);
        int y = dsu.Find(q);
        if (edges.count({x, y}) || edges.count({y, x})) return 1;
      }
    }
    return 2;
  };
  REP(Q) {
    int s, t; cin >> s >> t;
    s--, t--;
    cout << query(s, t) << '\n';
  }
}
