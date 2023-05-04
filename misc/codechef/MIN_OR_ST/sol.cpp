#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

const int maxn = 1e5+5;
int N, M, Q;

vector<array<int, 3>> adj[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> Q;
  vector<array<int, 3>> edges;
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].push_back({b, w, i});
    adj[b].push_back({a, w, i});
    edges.push_back({a, b, w});
  }
  vector<bool> blocked(M), cur_blocked(M);

  auto calc = [&](const vector<int>& v) -> int {
    vector<int> in(N+1);
    for (auto i: v) in[i] = 1;
    int ans = 0;
    vector<bool> vis(N+1);
    vector<bool> myb(M), curb(M);
    auto dfs = y_combinator([&](auto dfs, int i, int& c) -> void {
      if (!in[i]) return;
      if (!vis[i]) {
        vis[i] = 1;
        c++;
        for (auto& [j, w, id]: adj[i]) {
          if (blocked[id] || cur_blocked[id] || myb[id] || curb[id]) continue;
          dfs(j, c);
        }
      }
    });
    F0Rd(d, 30) {
      vis.assign(N, false);
      F0R(i, M) {
        if (blocked[i] || cur_blocked[i] || myb[i]) continue;
        auto& [a, b, w] = edges[i];
        if (w & (1 << d)) curb[i] = 1;
      }
      int c = 0;
      dfs(v[0], c);
      if (c == sz(v)) {
        F0R(i, M) {
          if (curb[i]) {
            curb[i] = 0;
            myb[i] = 1;
          }
        }
      }
      if (c < sz(v)) {
        F0R(i, M) {
          curb[i] = 0;
        }
        ans |= 1 << d;
      }
    }
    return ans;
  };

  vector<pair<int, int>> queries;
  F0R(i, Q) {
    int a, b; cin >> a >> b;
    queries.push_back({a, b});
  }

  vector<int> vec(N); iota(all(vec), 1);
  int orig = calc(vec);

  vector<bool> is2(30);
  vector<vector<int>> which(30);
  vector<int> vals(30);

  F0Rd(d, 30) {
    F0R(i, M) {
      if (blocked[i]) continue;
      auto& [a, b, w] = edges[i];
      if (w & (1 << d)) cur_blocked[i] = 1;
    }

    vector<vector<int>> comps;
    vector<int> comp(N+1);
    vector<bool> vis(N+1);

    auto dfs = y_combinator([&](auto dfs, int i, vector<int>& c) -> void {
      if (!vis[i]) {
        vis[i] = 1;
        comp[i] = sz(comps);
        c.push_back(i);
        for (auto& [j, w, id]: adj[i]) {
          if (blocked[id] || cur_blocked[id]) continue;
          dfs(j, c);
        }
      }
    });

    FOR(i, 1, N+1) {
      if (!vis[i]) {
        vector<int> c;
        dfs(i, c);
        comps.push_back(c);
        if (sz(comps) >= 3) break;
      }
    }

    if (sz(comps) == 1) {
      F0R(i, M) {
        if (blocked[i]) continue;
        if (cur_blocked[i]) {
          cur_blocked[i] = 0;
          blocked[i] = 1;
        }
      }
    }
    else {
      if (sz(comps) == 2) {
        is2[d] = 1;
        which[d] = comp;
        F0R(i, 2) {
          vals[d] |= calc(comps[i]);
        }
      }
      F0R(i, M) {
        cur_blocked[i] = 0;
      }
    }
  }

  F0R(i, Q) {
    auto [x, y] = queries[i];
    int ans = orig;
    F0Rd(d, 30) {
      if (is2[d] && which[d][x] != which[d][y]) {
        ans = vals[d];
        break;
      }
    }
    cout << ans << '\n';
  }
}
