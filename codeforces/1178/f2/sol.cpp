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
    mod_int& operator/=(const mod_int& b) {
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
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

const int maxn = 1005, maxm = 1e6+6;
int N, M, A[maxm];

int dp[maxn][maxn];
pair<int, int> I[maxn];
int nxt[maxn];

mint f(int l, int r) {
  if (l > r) return 1;
  int& res = dp[l][r];
  if (res != -1) return res;
  pair<int, int> mn = {2e9, -1};
  for (int i = l; i <= r; i++) ckmin(mn, {A[i], i});
  auto [L, R] = I[mn.first];
  // cout << l << ' ' << r << ": " << mn.first << ' ' << L << ' ' << R << endl;
  assert(l <= L && R <= r);

  mint ans = 1;
  {
    int i = L;
    while (nxt[i] != -1) {
      ans *= f(i+1, nxt[i]-1);
      i = nxt[i];
    }
  }
  mint rs = 0;
  {
    stack<int> st;
    for (int j = R; j <= r; j++) {
      int x = A[j];
      if (x > mn.first) {
        if (j == I[x].first) st.push(x);
        if (j == I[x].second) {
          assert(!st.empty() && st.top() == x);
          st.pop();
        }
      }
      if (st.empty()) {
        rs += f(R+1, j) * f(j+1, r);
      }
    }
  }
  mint ls = 0;
  {
    stack<int> st;
    for (int j = L; j >= l; j--) {
      int x = A[j];
      if (x > mn.first) {
        if (j == I[x].second) st.push(x);
        if (j == I[x].first) {
          assert(!st.empty() && st.top() == x);
          st.pop();
        }
      }
      if (st.empty()) {
        ls += f(l, j-1) * f(j, L-1);
      }
    }
  }
  ans *= rs;
  ans *= ls;
  return res = ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  vector<int> v;
  F0R(i, M) {
    int x; cin >> x;
    if (v.empty() || x != v.back()) v.push_back(x);
  }
  FOR(i, 1, N+1) I[i] = {1e9, -1e9};
  F0R(i, sz(v)) {
    int x = v[i];
    ckmin(I[x].first, i);
    ckmax(I[x].second, i);
  }

  // check if invalid
  if (sz(v) >= 2 * N) {
    cout << 0 << '\n';
    return 0;
  }
  FOR(i, 1, N+1) {
    for (int j = I[i].first; j <= I[i].second; j++) {
      if (v[j] < i) {
        cout << 0 << '\n';
        return 0;
      }
    }
  }

  memset(dp, -1, sizeof dp);
  M = sz(v);
  map<int, vector<int>> mp;
  F0R(i, M) {
    A[i] = v[i];
    mp[A[i]].push_back(i);
  }
  memset(nxt, -1, sizeof nxt);
  for (auto [x, v]: mp) {
    F0R(idx, sz(v)-1) {
      nxt[v[idx]] = v[idx+1];
    }
  }

  cout << f(0, M-1) << '\n';
}