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
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (auto& x: a) cin >> x;
  for (auto& x: b) cin >> x;
  vector<int> as = a, bs = b;
  sort(all(as));
  sort(all(bs));
  map<int, pair<int,int>> mpa, mpb, mp;
  for (int i = 1; i <= 100; i++) {
    mpa[i] = {500, -500};
    mpb[i] = {500, -500};
  }
  F0R(i, n) {
    ckmin(mpa[as[i]].first, i);
    ckmax(mpa[as[i]].second, i);

    ckmin(mpb[bs[i]].first, i);
    ckmax(mpb[bs[i]].second, i);
  }
  vector<pair<int,pair<int,int>>> v;
  bool poss = true;
  F0R(i, n) {
    pair<int,int> p = {max(mpa[a[i]].first,  mpb[b[i]].first),
                       min(mpa[a[i]].second, mpb[b[i]].second)};
    if (p.first > p.second) {
      poss = false;
      break;
    }
    else {
      v.push_back({i, p});
    }
  }
  vector<int> p(n, -1);
  F0R(i, n) {
    pair<int,int> mn = {500, -1};
    F0R(j, sz(v)) {
      auto [l, r] = v[j].second;
      if (l <= i) {
        ckmin(mn, {r, j});
      }
    }
    if (mn.second == -1) {
      poss = false;
      break;
    }
    else {
      int idx = v[mn.second].first;
      p[idx] = i;
      v.erase(v.begin()+mn.second);
    }
  }
  if (!poss) {
    cout << -1 << '\n';
  }
  else {
    vector<bool> vis(n, false);
    vector<pair<int,int>> ans;
    auto dfs = y_combinator([&](auto dfs, int i, vector<int>& v) -> void {
      if (vis[i]) return;
      else {
        vis[i] = true;
        v.push_back(i);
        dfs(p[i], v);
      }
    });
    F0R(i, n) {
      if (vis[i]) continue;
      else {
        vector<int> cyc;
        dfs(i, cyc);
        for (int j = sz(cyc)-2; j >= 0; j--) {
          ans.push_back({cyc[j], cyc[j+1]});
        }
      }
    }

    cout << sz(ans) << '\n';
    for (auto [x, y]: ans) {
      cout << x+1 << ' ' << y+1 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

