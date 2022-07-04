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

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // returns true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

int solve() {
  int N; cin >> N;
  DSU dsu(N);
  vector<map<int, vector<pair<int,int>>>> adds(2);
  vector<map<int, vector<int>>> rems(2);
  vector<int> ts;
  F0R(i, N) {
    int c, l, r; cin >> c >> l >> r;
    adds[c][l].push_back({i, r});
    rems[c][r].push_back(i);

    ts.push_back(l);
    ts.push_back(r);
  }
  sort(all(ts)); ts.erase(unique(all(ts)), ts.end());

  vector<bool> dead(N, false);
  vector<set<pair<int,int>>> s(2); // right coord, id
  for (auto t: ts) {
    for (int c: {0, 1}) {
      for (auto [i, r]: adds[c][t]) {
        if (!s[c^1].empty()) {
          auto [rr, id] = *s[c^1].rbegin();
          for (auto [_, j]: s[c^1]) {
            dsu.Union(i, j);
            if (j != id) dead[j] = true;
          }
          s[c^1].clear();
          s[c^1].insert({rr, id});
        }
        s[c].insert({r, i});
      }
    }

    for (int c: {0, 1}) {
      for (int i: rems[c][t]) {
        if (!dead[i]) {
          assert(s[c].count({t, i}));
          s[c].erase({t, i});
        }
      }
    }
  }
  int ans = 0;
  F0R(i, N) if (dsu.Find(i) == i) ans++;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
