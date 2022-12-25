#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

      mod_int() : val(0) {}
      mod_int(int _val) : val(_val % MOD) {}

      mod_int operator+() const {
        return mod_int(val); 
      }
      mod_int operator-() const {
        return mod_int(MOD-val); 
      }
      mod_int inverse() const {
        assert(val != 0);
        return *this ^ (MOD - 2);
      }

      bool operator==(const mod_int& b) const {
        return val == b.val;
      }

      bool operator!=(const mod_int& b) const {
        return !(*this == b);
      }

      mod_int& operator+=(const mod_int& b) {
        val += b.val;
        if (val >= MOD) val -= MOD;
        return *this;
      }
      mod_int& operator-=(const mod_int& b) {
        return *this += -b;
      }
      mod_int& operator*=(const mod_int& b) {
        val = (1LL*val*b.val) % MOD;
        return *this;
      }
      mod_int& operator/=(const mod_int& b) {
        val = (1LL*val*b.inverse().val) % MOD;
        return *this;
      }

      mod_int& operator++(int) {
        return *this += 1;
      }

      mod_int& operator--(int) {
        return *this -= 1;
      }

      friend mod_int operator+(const mod_int& a, const mod_int& b) {
        mod_int c = a; c += b;
        return c;
      }
      friend mod_int operator-(const mod_int& a, const mod_int& b) {
        mod_int c = a; c -= b;
        return c;
      }
      friend mod_int operator*(const mod_int& a, const mod_int& b) {
        mod_int c = a; c *= b;
        return c;
      }
      friend mod_int operator/(const mod_int& a, const mod_int& b) {
        mod_int c = a; c /= b;
        return c;
      }

      friend mod_int operator^(mod_int a, int b) {
        mod_int res(1);
        while (b > 0) {
          if (b&1) res *= a;
          a *= a;
          b >>= 1;
        }
        return res;
      }

      friend ostream& operator<<(ostream& o, const mod_int& x) {
        return o << x.val;
      };
      friend istream& operator>>(istream& i, mod_int& x) {
        i >> x.val; x.val %= MOD;
        return i;
      }
    };
} 
//}}}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

namespace ModCombinatorics { // {{{
  vector<int> inv, _fac, _ifac;
  template<size_t N, int MOD>
    void init() {
      inv.resize(N);
      _fac.resize(N);
      _ifac.resize(N);
      inv[0] = inv[1] = 1;
      for (size_t i = 2; i < N; i++) {
        inv[i] = (MOD - (1LL * (MOD/i) * inv[MOD%i]) % MOD) % MOD;
      }
      _fac[0] = _ifac[0] = 1;
      for (size_t i = 1; i < N; i++) {
        _fac[i] = (1LL * i * _fac[i-1]) % MOD;
        _ifac[i] = (1LL * _ifac[i-1] * inv[i]) % MOD;
      }
    }

  mint choose(int n, int k) {
    if (n < k || k < 0) return 0;
    return mint(1) * _fac[n] * _ifac[k] * _ifac[n-k];
  }

  mint fac(int n) {
    return mint(_fac[n]);
  }

  mint ifac(int n) {
    return mint(_ifac[n]);
  }
}; 
// }}}
namespace MC = ModCombinatorics;

const int maxn = 3e5+5;
int N, K;

int A[maxn];
vector<int> adj[maxn];

mint count_ways(const vector<mint>& v, const vector<int> sizes) {
  int t = 0;
  for (int s: sizes) t += s;
  mint ans = MC::fac(t);
  for (int s: sizes) ans *= MC::ifac(s);
  for (mint x: v) ans *= x;
  return ans;
}

mint ways[maxn]; // # ways to destroy this subtree
int sub_size[maxn];
vector<int> cur[maxn];
vector<int> roots[maxn];
int need[maxn];
void dfs(int i, int p) {
  vector<mint> v;
  vector<int> sizes;
  sub_size[i] = 1;
  ways[i] = 1;

  bool isroot = false;
  if (cur[A[i]].empty()) {
    roots[A[i]].push_back(i);
    isroot = true;
  }
  cur[A[i]].push_back(i);

  for (int j: adj[i]) if (j != p) {
    dfs(j, i);
    sub_size[i] += sub_size[j];
    v.push_back(ways[j]);
    sizes.push_back(sub_size[j]);
  }

  if (isroot) need[A[i]] += sub_size[i];

  ways[i] = count_ways(v, sizes);
  
  cur[A[i]].pop_back();
}

pair<int, mint> ans[maxn][maxn];

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

  bool Union(int x, int y) { // returns true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  MC::init<300005, MOD>();
  cin >> N >> K;
  FOR(i, 1, N+1) {
    cin >> A[i];
  }
  
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int rt = 1; rt <= N; rt++) {
    for (int i = 1; i <= N; i++) {
      need[i] = 0;
      roots[i].clear();
      cur[i].clear();
    }
    dfs(rt, rt);
    for (int i = 1; i <= K; i++) {
      if (roots[i].empty()) {
        ans[rt][i] = {0, 0};
      }
      else {
        vector<mint> v;
        vector<int> sizes;
        for (auto r: roots[i]) {
          v.push_back(ways[r]);
          sizes.push_back(sub_size[r]);
        }

        ans[rt][i] = {need[i], count_ways(v, sizes)};
      }
    }
  }

  for (int c = 1; c <= K; c++) {
    DSU dsu(N);
    for (int i = 1; i <= N; i++) {
      for (int j: adj[i]) {
        if (A[i] != c && A[j] != c) dsu.Union(i, j);
      }
    }
    int best = N + 1;
    for (int i = 1; i <= N; i++) {
      ckmin(best, ans[i][c].first);
    }
    mint total = 0;
    for (int i = 1; i <= N; i++) {
      if (dsu.Find(i) == i && ans[i][c].first == best) {
        total += ans[i][c].second;
      }
    }

    if (best == N) {
      cout << 0 << '\n';
    }
    else {
      cout << total << '\n';
    }
  }
}
