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

const int maxn = 255, INF = 1e9;
int dp[maxn][maxn][maxn];
string rel[3];

int nxt[100005][26];

int main() {
  // ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  string s; cin >> s;
  F0R(j, 26) nxt[n][j] = INF;
  F0Rd(i, n) {
    F0R(j, 26) {
      if (j == s[i]-'a') nxt[i][j] = i+1;
      else nxt[i][j] = nxt[i+1][j];
    }
  }
  auto update = [&](int i, int j, int k) -> void {
    if (dp[i][j][k] < INF) {
      if (i+1 <= sz(rel[0])) {
        ckmin(dp[i+1][j][k], nxt[dp[i][j][k]][rel[0][i]-'a']);
      }
      if (j+1 <= sz(rel[1])) {
        ckmin(dp[i][j+1][k], nxt[dp[i][j][k]][rel[1][j]-'a']);
      }
      if (k+1 <= sz(rel[2])) {
        ckmin(dp[i][j][k+1], nxt[dp[i][j][k]][rel[2][k]-'a']);
      }
    }
  };
  F0R(i, maxn) F0R(j, maxn) F0R(k, maxn) {
    dp[i][j][k] = INF;
  }
  dp[0][0][0] = 0;
  REP(q) {
    char t; cin >> t;
    int idx; cin >> idx; idx--;
    if (t == '+') {
      char c; cin >> c;
      rel[idx].push_back(c);
      F0Rd(d, 2) {
        F0R(i, maxn) F0R(j, maxn) {
          if (idx == 0)      update(sz(rel[0])-d, i, j);
          else if (idx == 1) update(i, sz(rel[1])-d, j);
          else               update(i, j, sz(rel[2])-d);
        }
      }
    }
    else {
      F0R(i, maxn) F0R(j, maxn) {
        if (idx == 0)      dp[sz(rel[0])][i][j] = INF;
        else if (idx == 1) dp[i][sz(rel[1])][j] = INF;
        else               dp[i][j][sz(rel[2])] = INF;
      }
      rel[idx].pop_back();
    }

    cout << (dp[sz(rel[0])][sz(rel[1])][sz(rel[2])] < INF ? "YES" : "NO") << '\n';
  }
}
