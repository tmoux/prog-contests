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

string solve() {
  int N; cin >> N;
  vector<string> S(N);
  F0R(i, N) cin >> S[i];
  auto cv = [](char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    return c-'A'+26;
  };
  auto rcv = [](int i) {
    if (i < 26) return 'a' + i;
    return 'A' + (i - 26);
  };
  const int ALPHA = 52;
  vector next(N, vector<vector<int>>(ALPHA));
  F0R(i, N) {
    F0R(j, sz(S[i])) {
      next[i][cv(S[i][j])].push_back(j);
    }
  }

  auto getmask = [&](int c, int ch, int mask) -> int {
    vector<int> pos(N);
    int nmask = 0;
    F0R(i, N) {
      int j = (mask >> i) & 1;
      pos[i] = next[i][c][j];

      if (sz(next[i][ch]) > 0 && next[i][ch][0] > pos[i]) {

      }
      else if (sz(next[i][ch]) > 1 && next[i][ch][1] > pos[i]) {
        nmask |= 1 << i;
      }
      else {
        return -1;
      }
    }
    return nmask;
  };

  vector dp(ALPHA, vector<pair<int, int>>(1 << N, make_pair(-1, -1)));
  auto f = y_combinator([&](auto f, int c, int mask) -> pair<int, int> {
      if (dp[c][mask].first != -1) return dp[c][mask];
      dp[c][mask] = {1, -1};
      F0R(ch, ALPHA) {
        int nmask = getmask(c, ch, mask);
        if (nmask != -1) {
          auto p = f(ch, nmask);
          ckmax(dp[c][mask], {p.first+1, ch});
        }
      }
      return dp[c][mask];
  });

  auto recon = y_combinator([&](auto recon, string& ans, int c, int mask) -> void {
    ans += rcv(c);
    int ch = dp[c][mask].second;
    if (ch != -1) {
      int nmask = getmask(c, ch, mask);
      recon(ans, ch, nmask);
    }
  });


  pair<int, int> ans = {0, 0};
  F0R(c, ALPHA) {
    bool b = true;
    F0R(i, N) if (next[i][c].empty()) {
      b = false;
      break;
    }
    if (b) {
      ckmax(ans, {f(c, 0).first, c});
    }
  }

  if (ans.first == 0) {
    return "";
  }
  else {
    string s;
    recon(s, ans.second, 0);
    return s;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    auto s = solve();
    cout << sz(s) << '\n';
    cout << s << '\n';
  }
}
