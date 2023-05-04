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

mint solve() {
  int N, M; cin >> N >> M;
  vector<string> g(N);
  F0R(i, N) {
    cin >> g[i];
  }

  vector adj(N, vector<vector<pair<int, int>>>(M));

  vector blocked(N, vector<bool>(M, 0));
  bool poss = true;

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };
  auto ok = [&](int i, int j) {
    return valid(i, j) && g[i][j] == '.' && !blocked[i][j];
  };

  auto add_edge = [&](int x1, int y1, int x2, int y2) {
    if (ok(x1, y1) && ok(x2, y2)) {
      adj[x1][y1].push_back({x2, y2});
      adj[x2][y2].push_back({x1, y1});
    }
  };
  queue<array<int, 3>> q;
  vector sat(N, vector(M, vector<bool>(2, 0)));
  auto update = [&](int i, int j) {
    if (valid(i-1, j) && g[i-1][j] == '*') q.push({i-1, j, 1});
    if (valid(i+1, j) && g[i+1][j] == '*') q.push({i+1, j, 1});
    if (valid(i, j-1) && g[i][j-1] == '*') q.push({i, j-1, 0});
    if (valid(i, j+1) && g[i][j+1] == '*') q.push({i, j+1, 0});
  };

  F0R(i, N) {
    F0R(j, M) {
      if (g[i][j] == '*') {
        bool b = i == 0 || i == N-1;
        b |= (valid(i-1, j) && g[i-1][j] == '*');
        b |= (valid(i+1, j) && g[i+1][j] == '*');

        if (b) q.push({i, j, 1});

        b = j == 0 || j == M-1;
        b |= (valid(i, j-1) && g[i][j-1] == '*');
        b |= (valid(i, j+1) && g[i][j+1] == '*');

        if (b) q.push({i, j, 0});
      }
    }
  }
  while (!q.empty()) {
    auto [i, j, k] = q.front(); q.pop();
    if (k == 0) {
      if (!sat[i][j][0]) {
        // horiz
        sat[i][j][0] = 1;
        if (ok(i, j-1)) {
          if (!ok(i, j+1)) {
            blocked[i][j-1] = 1;
            update(i, j-1);
          }
        }
        else if (ok(i, j+1)) {
          blocked[i][j+1] = 1;
          update(i, j+1);
        }
        else poss = false;
      }
    }
    if (k == 1) {
      if (!sat[i][j][1]) {
        // vert
        sat[i][j][1] = 1;
        if (ok(i-1, j)) {
          if (!ok(i+1, j)) {
            blocked[i-1][j] = 1;
            update(i-1, j);
          }
        }
        else if (ok(i+1, j)) {
          blocked[i+1][j] = 1;
          update(i+1, j);
        }
        else poss = false;
      }
    }
  }
  // F0R(i, N) {
  //   F0R(j, M) {
  //     cout << blocked[i][j];
  //   }
  //   cout << '\n';
  // }
  F0R(i, N) {
    F0R(j, M) {
      if (g[i][j] == '*') {
        add_edge(i, j-1, i, j+1);
        add_edge(i-1, j, i+1, j);
      }
    }
  }
  if (!poss) return 0;
  vector vis(N, vector<bool>(M, 0));
  auto dfs = y_combinator([&](auto dfs, int i, int j, int& n, int& cnt) -> void {
    n++;
    vis[i][j] = 1;
    for (auto [ni, nj]: adj[i][j]) {
      if (blocked[ni][nj]) continue;
      cnt++;
      if (!vis[ni][nj]) {
        dfs(ni, nj, n, cnt);
      }
    }
  });
  mint ans = 1;
  F0R(i, N) {
    F0R(j, M) {
      if (!vis[i][j] && !blocked[i][j]) {
        int n = 0;
        int cnt = 0;
        dfs(i, j, n, cnt);
        cnt /= 2;
        if (cnt > n) return 0;
        else if (cnt == n) ans *= 2;
        else ans *= n;
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
