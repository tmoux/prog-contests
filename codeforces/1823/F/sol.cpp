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

struct rational {
  ll num, den;

  rational() : num(0), den(1) {}
  rational(ll _val) : num(_val), den(1) {}
  rational(ll _num, ll _den) : num(_num), den(_den) {}

  rational operator+() const {
    return rational(num, den);
  }
  rational operator-() const {
    return rational(-num, den);
  }
  rational inverse() const {
    assert(num != 0);
    return rational(den, num);
  }

  rational& operator+=(const rational& b) {
    ll D = den * b.den;
    ll N = num * b.den + b.num * den;
    ll gc = __gcd(N, D);
    N /= gc, D /= gc;
    num = N, den = D;
    return *this;
  }
  rational& operator-=(const rational& b) {
    return *this += -b;
  }
  rational& operator*=(const rational& b) {
    ll N = num * b.num;
    ll D = den * b.den;
    ll gc = __gcd(N, D);
    N /= gc, D /= gc;
    num = N, den = D;
    return *this;
  }
  rational& operator/=(const rational& b) {
    return *this *= b.inverse();
  }

  rational& operator+=(int b) {
    return *this += rational(b);
  }
  rational& operator-=(int b) {
    return *this -= rational(b);
  }
  rational& operator*=(int b) {
    return *this *= rational(b);
  }
  rational& operator/=(int b) {
    return *this /= rational(b);
  }

  friend rational operator+(const rational& a, const rational& b) {
    rational c = a; c += b;
    return c;
  }
  friend rational operator-(const rational& a, const rational& b) {
    rational c = a; c -= b;
    return c;
  }
  friend rational operator*(const rational& a, const rational& b) {
    rational c = a; c *= b;
    return c;
  }
  friend rational operator/(const rational& a, const rational& b) {
    rational c = a; c /= b;
    return c;
  }

  friend rational operator+(const rational& a, int b) {
    return a + rational(b);
  }
  friend rational operator-(const rational& a, int b) {
    return a - rational(b);
  }
  friend rational operator*(const rational& a, int b) {
    return a * rational(b);
  }
  friend rational operator/(const rational& a, int b) {
    return a / rational(b);
  }
  friend rational operator+(int a, const rational& b) {
    return rational(a) + b;
  }
  friend rational operator-(int a, const rational& b) {
    return rational(a) - b;
  }
  friend rational operator*(int a, const rational& b) {
    return rational(a) * b;
  }
  friend rational operator/(int a, const rational& b) {
    return rational(a) / b;
  }

  friend rational operator^(rational a, int b) {
    rational res(1);
    while (b > 0) {
      if (b&1) res *= a;
      a *= a;
      b >>= 1;
    }
    return res;
  }

  friend ostream& operator<<(ostream& o, const rational& x) {
    return o << x.num << "/" << x.den;
  };
  friend istream& operator>>(istream& i, rational& x) {
    x.den = 1;
    return i >> x.num;
  }
};

namespace ModInt {
  template<int MOD>
  struct mod_int {
    int val;

    operator int() const { return val; }
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
// using mint = rational;


const int maxn = 2e5+5;
int N, S, T;
vector<int> adj[maxn];
int d[maxn];

mint goup[maxn];
map<pair<int, int>, mint> prob; // probability we take edge i->j if we are at i
mint reach[maxn], E[maxn];

void dfs1(int i, int p) {
  mint probReturn = 0;
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs1(j, i);
    probReturn += goup[j] / d[i];
  }

  if (i == T || i == S) goup[i] = 0;
  else goup[i] = mint(1) / (d[i] * (1 - probReturn));
}

void dfs2(int i, int p) {
  mint probReturn = i == p ? mint(0) : prob[{p, i}] / d[i];
  for (int j: adj[i]) {
    if (j == p) continue;
    prob[{j, i}] = goup[j];
    probReturn += prob[{j, i}] / d[i];
  }

  for (int j: adj[i]) {
    if (j == p) continue;
    probReturn -= prob[{j, i}] / d[i];
    if (i ==  T) prob[{i, j}] = 0;
    else prob[{i, j}] = mint(1) / (d[i] * (1 - probReturn));
    probReturn += prob[{j, i}] / d[i];

    dfs2(j, i);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> S >> T;
  S--, T--;
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  F0R(i, N) d[i] = sz(adj[i]);

  dfs1(S, S);
  dfs2(S, S);

  vector<bool> vis(N);
  queue<int> q;
  q.push(S);
  reach[S] = 1;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    vis[i] = 1;
    for (int j: adj[i]) {
      if (vis[j]) continue;
      reach[j] = reach[i] * prob[{i, j}];
      q.push(j);
    }
  }

  F0R(i, N) {
    if (i == T) E[i] = 1;
    else if (reach[i].val == 0) continue;
    else {
      mint den = 0;
      for (int j: adj[i]) {
        den += prob[{j, i}];
      }
      den = 1 - den / d[i];
      E[i] = 1 / den;
    }
  }


  F0R(i, N) {
    cout << (reach[i] * E[i]) << ' ';
  }
  cout << '\n';
}
