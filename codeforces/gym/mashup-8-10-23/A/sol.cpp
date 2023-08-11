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

const int maxn = 2005;
int N, M, K, Q;

vector<array<int, 3>> garland[maxn];

int on[maxn];
int need[maxn][maxn];
array<int, 4> query[maxn];
ll ans[maxn];

struct FenwickTree2D {
  vector<vector<ll>> bit;
  int n, m;

  void init(int _n, int _m) {
    n = _n + 1;
    m = _m + 1;
    bit.resize(n+1, vector<ll>(m+1, 0));
  }

  ll sum(int x, int y) {
    ll ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
        ret += bit[i][j];
    return ret;
  }

  ll rec(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
  }

  void add(int x, int y, int delta) {
    for (int i = x; i < n; i = i | (i + 1))
      for (int j = y; j < m; j = j | (j + 1))
        bit[i][j] += delta;
  }

};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  F0R(i, K) {
    int l; cin >> l;
    garland[i].resize(l);
    F0R(j, l) {
      int x, y, w; cin >> x >> y >> w;
      garland[i][j] = {x, y, w};
    }
  }

  F0R(i, K) on[i] = 1;
  cin >> Q;
  int q = 0;
  REP(Q) {
    string s; cin >> s;
    if (s == "SWITCH") {
      int i; cin >> i; i--;
      on[i] ^= 1;
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      F0R(i, K) need[q][i] = on[i];
      query[q] = {x1, y1, x2, y2};
      q++;
    }
  }
  FenwickTree2D fen; fen.init(N, M);
  F0R(i, K) {
    for (auto [x, y, w]: garland[i]) {
      fen.add(x, y, w);
    }
    F0R(j, q) {
      if (need[j][i]) {
        auto [x1, y1, x2, y2] = query[j];
        ans[j] += fen.rec(x1, y1, x2, y2);
      }
    }
    for (auto [x, y, w]: garland[i]) {
      fen.add(x, y, -w);
    }
  }
  F0R(i, q) {
    cout << ans[i] << '\n';
  }
}
