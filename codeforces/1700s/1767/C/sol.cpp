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
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

const int maxn = 105;
int N;

vector<pair<int, int>> invls;

int dp[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;

  vector<pair<int, int>> vs;
  F0R(i, N) {
    FOR(j, i, N) {
      int x; cin >> x;
      if (x == 1) {
        vs.push_back({i, j});
      }
      else if (x == 2) {
        invls.push_back({i, j});
      }
    }
  }
  F0R(i, N) vs.push_back({i, i});

  // merge vs
  pair<int, int> cur = {0, 0};
  sort(all(vs));
  vector<pair<int, int>> Ds;
  for (auto [l, r]: vs) {
    if (l > cur.second) {
      Ds.push_back(cur);
      cur = {l, r};
    }
    else {
      ckmax(cur.second, r);
    }
  }
  Ds.push_back(cur);

  auto find_index = [&](int x) -> int {
    F0R(i, sz(Ds)) {
      if (Ds[i].first <= x && x <= Ds[i].second) {
        return i;
      }
    }
    assert(false);
  };

  vector<int> latest(sz(Ds), -1);
  for (auto [l, r]: invls) {
    int i = find_index(r);
    int j = find_index(l);
    ckmax(latest[i], j);

    if (i == j) {
      // impossible, exit
      // cout << "exiting " << i << ' ' << j << endl;
      cout << 0 << '\n';
      return 0;
    }
  }
  for (int i = 1; i < sz(Ds); i++) {
    ckmax(latest[i], latest[i-1]);
  }

  // cout << Ds << endl;

  FOR(i, 0, sz(Ds)) {
    mint res = dp[i];
    for (int j = latest[i]+1; j <= i; j++) {
      if (j == 0) {
        res += 2;
      }
      else {
        res += mint(dp[j-1]);
      }
    }
    dp[i] = res.val;
  }

  /*
  F0R(i, sz(Ds)) {
    cout << i << ": " << dp[i] << endl;
  }
  */

  mint ans = dp[sz(Ds)-1];

  cout << ans << '\n';
}
