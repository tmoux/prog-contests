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

// 0 = blank, 1 = X, 2 = O
using state = array<int, 9>;

int is_winning(state s) {
  auto win = [&](int a, int b, int c, int X) -> bool {
    return s[a] == X && s[b] == X && s[c] == X;
  };
  vector<array<int, 3>> wins = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},

    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},

    {0, 4, 8},
    {2, 4, 6},
  };
  for (auto [a, b, c]: wins) {
    if (win(a, b, c, 1)) return 0;
  }
  for (auto [a, b, c]: wins) {
    if (win(a, b, c, 2)) return 1;
  }

  return -1;
}

void add(array<int, 2>& a, array<int, 2> b) {
  a[0] += b[0];
  a[1] += b[1];
}
array<int, 2> operator+(array<int, 2> a, array<int, 2> b) {
  return {a[0] + b[0], a[1] + b[1]};
}

map<state, array<int, 2>> dp;
array<int, 2> f(state s, int turn) {
  if (dp.count(s)) return dp[s];

  int w = is_winning(s);
  if (w == 0)      return dp[s] = {1, 0};
  else if (w == 1) return dp[s] = {0, 1};


  int place = turn == 0 ? 1 : 2;
  auto& res = dp[s] = {0, 0};
  dp[s] = {0, 0};
  F0R(i, 9) if (s[i] == 0) {
    s[i] = place;
    add(res, f(s, turn^1));
    s[i] = 0;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  state s = {0};
  f(s, 0);

  map<char, int> mp = {
    {'.', 0},
    {'X', 1},
    {'O', 2},
  };

  int T; cin >> T;
  while (T--) {
    string s; cin >> s;
    state d;
    F0R(i, 9) {
      d[i] = mp[s[i]];
    }
    if (!dp.count(d)) {
      cout << "-1 -1\n";
    }
    else {
      auto [x, y] = dp[d];
      cout << x << ' ' << y << '\n';
    }
  }
}
