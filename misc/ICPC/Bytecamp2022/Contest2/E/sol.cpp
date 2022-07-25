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

char to[] = {'R', 'P', 'S'};
map<char, int> from = {
  {'R', 0},
  {'P', 1},
  {'S', 2},
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, T; cin >> N >> T;
  string s; cin >> s;

  vector<int> d;
  for (char c: s) d.push_back(from[c]);

  vector<pair<int, int>> v;
  int cur = 0;
  F0R(i, sz(d)) {
    cur++;
    if (i == sz(d)-1 || d[i] != d[i+1]) {
      v.push_back({d[i], cur});
      cur = 0;
    }
  }

  vector<pair<int, int>> ans;
  F0R(i, sz(v)) {
    if (i + 1 == sz(v) || v[i].first != (v[i+1].first + 1) % 3) {
      ans.push_back(v[i]);
    }
    else {
      int mn = min(v[i].second, T);
      ans.push_back({v[i].first, v[i].second - mn});
      ans.push_back(v[i+1]);
      if (i+2 < sz(v) && v[i].first == v[i+2].first) {
        v[i+2].second += mn;
      }
      else {
        ans.push_back({v[i].first, mn});
      }
      i++;
    }
  }

  // output
  for (auto [x, cnt]: ans) {
    REP(cnt) cout << to[x];
  }
  cout << '\n';
}
