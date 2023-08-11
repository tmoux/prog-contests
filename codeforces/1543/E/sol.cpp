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

void solve(int tc) {
  int N; cin >> N;
  vector<vector<int>> adj(1 << N);
  F0R(i, N * (1 << (N-1))) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  auto F = y_combinator([&](auto F, int n, vector<int> v) -> vector<pair<int, int>> {
      if (sz(v) == 1) {
        assert(v[0] == 0);
        return {{0, 0}};
      }
      vector<int> in(1 << N, 0);
      for (auto i: v) in[i] = 1;
      assert(in[0]);
      int u = -1;
      for (int j: adj[0]) {
        if (in[j]) {
          u = j;
          break;
        }
      }

      vector<int> pr(1 << N);
      vector<int> lower;
      queue<int> ql, qu, nql, nqu;
      ql.push(0);
      qu.push(u);
      vector<int> visl(1 << N, 0), visu(1 << N, 0);
      visl[0] = 1;
      visu[u] = 1;
      while (!ql.empty() && !qu.empty()) {
        while (!ql.empty()) {
          int i = ql.front(); ql.pop();
          lower.push_back(i);
          for (int j: adj[i]) {
            if (in[j]) {
              if (visl[j]) continue;
              if (!visu[j]) {
                visl[j] = 1;
                nql.push(j);
              }
              else pr[i] = j;
            }
          }
        }
        while (!qu.empty()) {
          int i = qu.front(); qu.pop();
          for (int j: adj[i]) {
            if (in[j]) {
              if (visu[j]) continue;
              if (!visl[j]) {
                visu[j] = 1;
                nqu.push(j);
              }
            }
          }
        }

        ql = nql;
        qu = nqu;

        while (!nql.empty()) nql.pop();
        while (!nqu.empty()) nqu.pop();

      }

      auto r = F(n-1, lower);
      vector<pair<int, int>> ans = r;
      for (auto [i, pos]: r) {
        ans.push_back({pr[i], pos + (1 << (n-1))});
      }
      return ans;
  });

  vector<int> v(1 << N); iota(all(v), 0);
  auto ans = F(N, v);
  vector<int> perm(1 << N, -1); // index at position
  for (auto [i, pos]: ans) {
    perm[pos] = i;
  }

  F0R(i, 1 << N) {
    cout << perm[i] << ' ';
  }
  cout << '\n';

  if (N == 1 || N == 2 || N == 4 || N == 8 || N == 16) {
    vector<int> color(1 << N);
    F0R(mask, 1 << N) {
      F0R(i, N) {
        color[mask] ^= i * ((mask >> i) & 1);
      }
    }
    vector<int> pColor(1 << N);
    F0R(i, 1 << N) {
      pColor[perm[i]] = color[i];
    }
    F0R(i, 1 << N) {
      cout << pColor[i] << ' ';
    }
    cout << '\n';
  }
  else {
    cout << -1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tt, 1, T+1) solve(tt);
}
