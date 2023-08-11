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

mint solve() {
  int N, M, H; cin >> N >> M >> H;
  vector<vector<int>> G(N, vector<int>(M));

  vector<vector<int>> adj(N+M);
  F0R(i, N) F0R(j, M) {
    cin >> G[i][j];
    if (G[i][j] != -1) {
      adj[i].push_back(j + N);
      adj[j + N].push_back(i);
    }
  }

  auto check = [&]() -> bool {
    vector<int> x(N, -1), y(M, -1);

    auto dfs = [&](auto dfs, int i, int j) -> void {
      if (x[i] == -1 && y[j] != -1) {
        x[i] = (2 * H - G[i][j] - y[j]) % H;
        for (int k: adj[i]) dfs(dfs, i, k-N);
      }
      else if (x[i] != -1 && y[j] == -1) {
        y[j] = (2 * H - G[i][j] - x[i]) % H;
        for (int k: adj[j+N]) dfs(dfs, k, j);
      }
    };
    F0R(i, N) {
      if (x[i] == -1) {
        x[i] = 0;
      }
      F0R(j, M) if (G[i][j] != -1) dfs(dfs, i, j);
    }

    F0R(i, N) F0R(j, M) {
      if (G[i][j] != -1) {
        if (x[i] != -1 && y[j] != -1) {
          if ((x[i] + y[j] + G[i][j]) % H != 0) return false;
        }
      }
    }
    return true;
  };

  if (!check()) {
    return 0;
  }
  else {
    vector<bool> vis(N + M, false); 
    auto dfs = [&](auto dfs, int i) -> void {
      vis[i] = true;      
      for (int j: adj[i]) if (!vis[j]) dfs(dfs, j);
    };
    int comps = 0;
    F0R(i, N+M) if (!vis[i]) dfs(dfs, i), comps++;

    int e = comps - 1;
    return mint(H) ^ e;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
