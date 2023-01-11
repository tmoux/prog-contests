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
} //}}}
using mint = ModInt::mod_int<998244353>;

mint solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  vector<int> occ(N+1);
  vector<multiset<int>> indices(N+1);
  F0R(i, N) {
    cin >> A[i];
    occ[A[i]]++;
    indices[A[i]].insert(i);
  }
  F0R(i, N) {
    cin >> B[i];
    occ[B[i]]++;
    indices[B[i]].insert(i);
  }
  for (int i = 1; i <= N; i++) {
    if (occ[i] == 0) {
      return 0;
    }
  }
  vector<bool> used(N, false);

  queue<pair<int, int>> q;
  F0R(i, N) {
    if (occ[A[i]] == 1) q.push({A[i], i});
    if (occ[B[i]] == 1) q.push({B[i], i});
  }
  while (!q.empty()) {
    auto [x, i] = q.front(); q.pop();
    int y = A[i] == x ? B[i] : A[i];
    used[i] = true;
    auto it = indices[x].find(i); indices[x].erase(it);
    it = indices[y].find(i); indices[y].erase(it);
    if (sz(indices[y]) == 0) return 0;
    else if (sz(indices[y]) == 1) {
      q.push({y, *indices[y].begin()});
    }
  }

  /*
  F0R(i, N) {
    if (occ[A[i]] == 1) {
      used[i] = true;
      occ[A[i]]--;
      if (occ[B[i]] == 1) {
        // not possible
        return 0;
      }
      else occ[B[i]]--;
    }
  }
  */
  // count doubles
  int doubles = 0;
  F0R(i, N) {
    if (!used[i]) {
      if (A[i] == B[i]) {
        doubles++;
        used[i] = true;
      }
    }
  }

  vector<vector<int>> adj(N);
  vector<vector<int>> places(N+1);
  F0R(i, N) {
    if (!used[i]) {
      places[A[i]].push_back(i);
      places[B[i]].push_back(i);
    }
  }
  for (int i = 1; i <= N; i++) {
    assert(sz(places[i]) == 2 || sz(places[i]) == 0);
    if (!places[i].empty()) {
      adj[places[i][0]].push_back(places[i][1]);
      adj[places[i][1]].push_back(places[i][0]);
    }
  }
  int cycles = 0;
  vector<bool> vis(N, false);
  auto dfs = y_combinator([&](auto dfs, int i) -> void {
    vis[i] = true;
    for (int j: adj[i]) if (!vis[j]) {
      dfs(j);
    }
  });
  F0R(i, N) {
    if (!used[i] && !vis[i]) {
      cycles++;
      dfs(i);
    }
  }

  // cout << adj << endl;
  // DEBUG(cycles);
  // DEBUG(doubles);
  mint ans = (mint(2) ^ cycles) * (mint(N) ^ doubles);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
