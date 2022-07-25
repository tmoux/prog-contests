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
  int N; cin >> N;

  auto top2 = [](const multiset<int>& ms) -> int {
    int ans = 0;
    if (!ms.empty()) ans += *prev(ms.end());
    if (sz(ms) >= 2) ans += *prev(prev(ms.end()));
    return ans;
  };

  auto solve = [&](vector<array<int, 3>> v) -> int {
    map<int, int> mp;
    for (auto [x, y, z]: v) mp[y] += z;
    vector<int> ys;
    for (auto [_, z]: mp) ys.push_back(z);
    sort(all(ys), greater<int>());
    int ans = 0;
    for (int i = 0; i < min(3, sz(ys)); i++) {
      ans += ys[i];
    }

    multiset<int> ms;
    for (auto [_, z]: mp) ms.insert(z);
    map<int, vector<pair<int, int>>> mp2;
    for (auto [x, y, z]: v) mp2[x].push_back({y, z});
    for (const auto& [x, vec]: mp2) {
      int tr = 0;
      for (auto [y, z]: vec) {
        tr += z;
        auto it = ms.find(mp[y]);
        ms.erase(it);
        ms.insert(mp[y] - z);
      }

      tr += top2(ms);

      for (auto [y, z]: vec) {
        auto it = ms.find(mp[y] - z);
        ms.erase(it);
        ms.insert(mp[y]);
      }
      ckmax(ans, tr);
    }
    return ans;
  };

  vector<array<int, 3>> v(N);
  F0R(i, N) {
    F0R(j, 3) cin >> v[i][j];
  }

  int ans = solve(v);
  F0R(i, N) swap(v[i][0], v[i][1]);
  ckmax(ans, solve(v));
  cout << ans << '\n';
}
