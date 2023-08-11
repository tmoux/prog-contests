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

namespace ModInt {
  template<int MOD>
  struct mod_int {
    int val;

    operator int() const { return val; }
    mod_int() : val(0) {}
    mod_int(ll _val) : val((_val + MOD) % MOD) {}

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
    mod_int& operator/=(const mod_int& b) const {
      val = (1LL*val*b.inverse().val) % MOD;
      return *this;
    }

    mod_int& operator+=(int b) {
      return *this += mod_int(b);
    }
    mod_int& operator-=(int b) {
      return *this -= mod_int(b);
    }
    mod_int& operator*=(int b) {
      return *this *= mod_int(b);
    }
    mod_int& operator/=(int b) {
      return *this /= mod_int(b);
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

    friend mod_int operator+(const mod_int& a, int b) {
      return a + mod_int(b);
    }
    friend mod_int operator-(const mod_int& a, int b) {
      return a - mod_int(b);
    }
    friend mod_int operator*(const mod_int& a, int b) {
      return a * mod_int(b);
    }
    friend mod_int operator/(const mod_int& a, int b) {
      return a / mod_int(b);
    }
    friend mod_int operator+(int a, const mod_int& b) {
      return mod_int(a) + b;
    }
    friend mod_int operator-(int a, const mod_int& b) {
      return mod_int(a) - b;
    }
    friend mod_int operator*(int a, const mod_int& b) {
      return mod_int(a) * b;
    }
    friend mod_int operator/(int a, const mod_int& b) {
      return mod_int(a) / b;
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
      return i >> x.val;
    }
  };
}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

// Find cycles and bridges
// Then do DP on (i, xor) = # ways to get this xor

using vi = vector<int>;
using pii = pair<int, int>;

int S = 0;
vector<vi> C;
namespace BC {
  vi num, st;
  vi wt;
  vector<vector<pii>> ed;
  vector<pii> edges, bridges;
  int Time;
  template<class F>
  int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
          top = min(top, num[y]);
          if (num[y] < me)
            st.push_back(e);
        } else {
          int si = sz(st);
          int up = dfs(y, e, f);
          top = min(top, up);
          if (up == me) { // BCC (list of edges)
            st.push_back(e);
            f(vi(st.begin() + si, st.end()));
            st.resize(si);
          }
          else if (up < me) st.push_back(e);
          else { // BRIDGE
            // S ^= wt[e];
            // auto [a, b] = edges[e];
            // bridges.emplace_back(a, b);
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
} using namespace BC;

int MX = 1 << 17;

using vmi = vector<mint>;

template<typename T>
T INV = 1;
template<> mint INV<mint> = mint(MX).inverse();

template<typename T>
void FST(vector<T>& a, bool inv, T INV) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) FOR(j,i,i+step) {
        auto &u = a[j], &v = a[j + step]; tie(u, v) =
                                           // inv ? pii(v - u, u) : pii(v, u + v); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
        pii(u + v, u - v);                   // XOR /// include-line
      }
  }
  if (inv) for (auto& x : a) x *= INV; // XOR only /// include-line
}

template<typename T>
vector<T> conv(vector<T> a, vector<T> b) {
  FST(a, 0, INV<T>); FST(b, 0, INV<T>);
  FOR(i,0,sz(a)) a[i] *= b[i];
  FST(a, 1, INV<T>); return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M;
  cin >> N >> M;
  ed.resize(N);
  wt.resize(M);
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    a--, b--;
    wt[i] = w;
    S ^= w;
    ed[a].emplace_back(b, i);
    ed[b].emplace_back(a, i);
  }

  bicomps([&](const vi& edgelist) {
    vi r;
    for (auto e: edgelist) {
      r.push_back(wt[e]);
    }
    C.push_back(r);
  });

  assert(sz(C) <= 50);
  vector<mint> dp(MX, 0); dp[S] = 1;
  vector<mint> dp2(MX, 0); dp2[S] = 1;
  for (auto c: C) {
    vector<mint> mult(MX, 0);
    vector<mint> mult2(MX, 0);
    for (auto i: c) {
      mult[i] += 1;
      mult2[i] = 1;
    }
    dp = conv(dp, mult);
    dp2 = conv(dp2, mult2);
    F0R(i, MX) dp2[i] = dp2[i] == 0 ? 0 : 1;
  }

  for (int x = 0; x < MX; x++) {
    if (dp2[x] != 0) {
      cout << x << ' ' << dp[x] << '\n';
      return 0;
    }
  }
}
