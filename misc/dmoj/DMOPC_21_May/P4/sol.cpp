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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> g(N, vector<int>(M));
  auto solve = [&]<typename F>(vector<int> v, F &lambda) -> void {
    int j = 0;
    while (j < sz(v)) {
      if (v[j] == 1) {
        lambda(j);
        if (j < sz(v)-1) v[j+1] ^= 1;
        j++;
      }
      else {
        int k = j;
        while (v[k] == 0) k++;
        for (int l = k; l >= j; l--) {
          lambda(l);
        }
        if (k < sz(v)-1) v[k+1] ^= 1;
        j = k+1;
      }
    }
  };
  int cnt = 0;
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, M) {
      g[i][j] = s[j] == 'H' ? 1 : 0;
      if (g[i][j]) {
        cnt++;
      }
      else {
      }
    }
  }
  if (cnt&1) {
    vector<pair<int,int>> ans;
    auto F = [&](int i) -> void {
      auto f = [&](int j) -> void {
        ans.push_back({i, j});
      };
      solve(g[i], f);
      // flip neighboring rows
      if (i > 0) {
        F0R(j, M) g[i-1][j] ^= 1;
      }
      if (i < N-1) {
        F0R(j, M) g[i+1][j] ^= 1;
      }
    };

    vector<int> row_parity(N, 0);
    F0R(i, N) {
      F0R(j, M) {
        row_parity[i] ^= g[i][j];
      }
    }
    solve(row_parity, F);
    for (auto [x, y]: ans) {
      cout << x+1 << ' ' << y+1 << '\n';
    }
  }
  else {
    cout << -1 << '\n';
  }
}

