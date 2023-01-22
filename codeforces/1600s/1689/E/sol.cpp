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

void solve() {
  int N; cin >> N;
  int ops = 0;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    if (A[i] == 0) {
      ops++;
      A[i] = 1;
    }
  }
  vector<vector<int>> adj(N, vector<int>(N));
  F0R(i, N) {
    F0R(j, N) {
      adj[i][j] = (A[i] & A[j]) > 0;
    }
  }
  vector<vector<int>> comps;
  vector<bool> vis(N, false);
  auto dfs = y_combinator([&](auto dfs, int i, vector<int>& v) -> void {
    if (!vis[i]) {
      vis[i] = true;
      v.push_back(i);
      F0R(j, N) if (adj[i][j]) dfs(j, v);
    }
  });
  F0R(i, N) {
    if (!vis[i]) {
      vector<int> v;
      dfs(i, v);
      comps.push_back(v);
    }
  }

  if (sz(comps) > 1) {
    pair<int, vector<int>> best = {0, {}};
    const int MX = 30;
    for (auto v: comps) {
      int l = 1<<MX;
      for (auto i: v) ckmin(l, A[i] & -A[i]);
      ckmax(best, {l, v});
    }
    auto v = best.second;
    if (sz(v) == 1) {
      ops++;
      A[v[0]]--;
    }
    else {
      // check if can do 1
      vector<vector<int>> G(MX, vector<int>(MX, 0));
      vector<int> W(MX);
      F0R(i, N) {
        F0R(j, MX) {
          F0R(k, MX) {
            if ((A[i] & (1<<j)) && (A[i] & (1<<k))) {
              G[j][k]++;
            }
          }
          if (A[i] & (1<<j)) W[j]++;
        }
      }
      auto upd = [&](int i, int del) {
        F0R(j, MX) if (A[i] & (1<<j)) W[j]--;
        F0R(j, MX) F0R(k, MX) {
          if ((A[i] & (1<<j)) && (A[i] & (1<<k))) {
            G[j][k]--;
          }
        }
        A[i] += del;
        F0R(j, MX) if (A[i] & (1<<j)) W[j]++;
        F0R(j, MX) F0R(k, MX) {
          if ((A[i] & (1<<j)) && (A[i] & (1<<k))) {
            G[j][k]++;
          }
        }
      };
      auto check = [&]() -> bool {
        // check if there is only one CC with nonzero weight
        F0R(i, N) if (A[i] == 0) return false;
        vector<bool> vis(MX, false);
        int nonzero = 0;
        auto dfs = y_combinator([&](auto dfs, int i, int& w) -> void {
          if (!vis[i]) {
            vis[i] = true;
            w += W[i];
            F0R(j, MX) if (G[i][j] > 0) dfs(j, w);
          }
        });
        F0R(j, MX) {
          if (!vis[j]) {
            int w = 0;
            dfs(j, w);
            if (w > 0) nonzero++;
          }
        }
        return nonzero == 1;
      };
      F0R(i, N) {
        upd(i, 1);
        if (check()) {
          ops++;
          goto done;
        }
        upd(i, -2);
        if (check()) {
          ops++;
          goto done;
        }
        upd(i, 1);
      }
      // can always do 2
      ops += 2;
      assert(sz(v) >= 2);
      A[v[0]]--, A[v[1]]++;
    }
  }

  done:
  cout << ops << '\n';
  F0R(i, N) {
    cout << A[i] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
