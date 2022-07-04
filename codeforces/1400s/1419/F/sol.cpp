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

struct DSU { // {{{ 
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

  int getCompSizes(const vector<int>& v) {
    set<int> s;
    for (auto i: v) s.insert(Find(i));
    int r = 0;
    for (auto i: s) r += -par[i];
    return r;
  }
}; // }}}

// given range [l, r), returns the first i s.t. f(i) is false
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;

  // {{{
  map<int, vector<pair<int, int>>> xs, ys;
  set<pair<int, int>> S;
  vector<array<int, 2>> P(N);
  F0R(i, N) {
    int x, y; cin >> x >> y;
    P[i] = {x, y};
    S.insert({x, y});
    xs[x].push_back({y, i});
    ys[y].push_back({x, i});
  }
  for (auto& [_, v]: xs) sort(all(v));
  for (auto& [_, v]: ys) sort(all(v));
  // }}}

  vector<int> V; // {{{
  vector<array<int, 3>> edges;
  vector<array<int, 3>> type1;
  vector<pair<int, vector<int>>> type2;
  F0R(i, N) {
    auto add_edge = [&](int j, int w) -> void {
      edges.push_back({i, j, w});
      type1.push_back({(w+1)/2, i, j});
      V.push_back(w);
      V.push_back((w+1)/2);
    };
    auto [x, y] = P[i];

    auto it = lower_bound(all(xs[x]), make_pair(y, i));
    if (next(it) != xs[x].end()) {
      auto [ny, j] = *next(it);
      int w = ny - y;
      add_edge(j, w);
    }

    it = lower_bound(all(ys[y]), make_pair(x, i));
    if (next(it) != ys[y].end()) {
      auto [nx, j] = *next(it);
      int w = nx - x;
      add_edge(j, w);
    }
  } // }}}

  auto add_type2 = [&](int x, int y) { // {{{
    vector<pair<int, int>> Ws;
    auto it = lower_bound(all(xs[x]), make_pair(y, 0));
    if (it != xs[x].end()) {
      auto [ny, j] = *it;
      int w = ny - y;
      Ws.push_back({w, j});
    }
    if (it != xs[x].begin()) {
      auto [ny, j] = *prev(it);
      int w = y - ny;
      Ws.push_back({w, j});
    }

    it = lower_bound(all(ys[y]), make_pair(x, 0));
    if (it != ys[y].end()) {
      auto [nx, j] = *it;
      int w = nx - x;
      Ws.push_back({w, j});
    }
    if (it != ys[y].begin()) {
      auto [nx, j] = *prev(it);
      int w = x - nx;
      Ws.push_back({w, j});
    }

    assert(sz(Ws) >= 2);
    sort(all(Ws));
    for (int i = 1; i < sz(Ws); i++) {
      int W = Ws[i].first;
      vector<int> v;
      for (int j = 0; j <= i; j++) {
        v.push_back(Ws[j].second);
      }
      type2.push_back({W, v});
      V.push_back(W);
    }
  }; // }}}

  set<pair<int, int>> used; // {{{
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (P[i][0] != P[j][0] && P[i][1] != P[j][1]) {
        auto [x1, y1] = P[i];
        auto [x2, y2] = P[j];

        if (!S.count({x1, y2}) && !used.count({x1, y2})) {
          add_type2(x1, y2);
          used.insert({x1, y2});
        }
        if (!S.count({x2, y1}) && !used.count({x2, y1})) {
          add_type2(x2, y1);
          used.insert({x2, y1});
        }
      }
    }
  } // }}}
  sort(all(type1));
  sort(all(type2));

  auto check = [&](int D) -> bool { // {{{
    DSU dsu(N);
    for (auto [i, j, w]: edges) {
      if (w <= D) dsu.Union(i, j);
    }
    if (dsu.getCompSizes({0}) == N) return true;
    for (const auto& [w, i, j]: type1) {
      if (w <= D) {
        if (dsu.getCompSizes({i, j}) == N) return true;
      }
      else break;
    }
    for (const auto& [w, v]: type2) {
      if (w <= D) {
        if (dsu.getCompSizes(v) == N) return true;
      }
      else break;
    }
    return false;
  }; // }}}

  sort(all(V)); V.erase(unique(all(V)), V.end());
  int idx = find_first_false(0, sz(V), [&](int x) {
      return !check(V[x]);
  });
  cout << (idx == sz(V) ? -1 : V[idx]) << '\n';
}
