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
  string s; cin >> s;
  map<char, vector<int>> mp;
  F0R(i, n) {
    mp[s[i]].push_back(i);
  }

  pair<int, string> ans = {n, ""};
  auto check = [&](int d) -> void {
    if (n/d > 26) return;
    vector<pair<int, char>> v;
    for (auto [c, vec]: mp) {
      v.push_back({max(0, d - sz(vec)), c});
    }
    sort(all(v));
    vector<int> extras;
    vector<bool> used(n, false);
    F0R(i, min(n/d, sz(v))) {
      int c = v[i].second;
      F0R(j, min(sz(mp[c]), d)) used[mp[c][j]] = true;
    }
    F0R(i, n) if (!used[i]) extras.push_back(i);

    set<char> ch_used;
    for (auto [_, c]: v) ch_used.insert(c);
    F0R(i, 26) {
      char c = i + 'a';
      if (!ch_used.count(c) && sz(v) < n/d) {
        v.push_back({0, c});
      }
    }
    // cout << ch_used << endl;
    // DEBUG(n/d);
    assert(sz(v) >= n/d);
    string t(n, '#');
    int diff = 0;
    F0R(i, n/d) {
      int cnt = 0;
      char c = v[i].second;
      for (int j: mp[c]) if (cnt < d) t[j] = c, cnt++;
      while (cnt < d) {
        assert(!extras.empty());
        int j = extras.back(); extras.pop_back();
        t[j] = c;
        cnt++;
        diff++;
      }
    }
    int cnt = 0;
    F0R(i, n) {
      if (s[i] != t[i]) cnt++;
    }
    assert(extras.empty());
    assert(cnt == diff);
    ckmin(ans, {diff, t});
  };

  for (int d = 1; d*d <= n; d++) {
    if (n % d == 0) {
      check(d);
      check(n/d);
    }
  }

  cout << ans.first << '\n';
  cout << ans.second << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
