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

int solve() {
  int N, M; cin >> N >> M;
  string s, t; cin >> s >> t;

  const int INV = 2e9;
  vector<vector<int>> dpl(N+1, vector<int>(M+1, -1));
  vector<vector<int>> dpr(N+1, vector<int>(M+1, -1));

  {
    vector<int> prev_char(26, -1);
    for (int i = 0; i <= N; i++) {
      dpl[i][0] = i == 0 ? INV : i-1;
      if (i > 0) {
        for (int j = 1; j <= M; j++) {
          int ni = prev_char[t[j-1]-'a'];
          if (ni != -1) {
            int p = dpl[ni][j-1];

            if (p == -1) dpl[i][j] = -1;
            else dpl[i][j] = ni < i-1 ? i-1 : p;
          }
        }
      }
      if (i < N) {
        prev_char[s[i]-'a'] = i;
      }
    }

    vector<int> next_char(26, -1);
    for (int i = N; i >= 0; i--) {
      if (i < N) next_char[s[i]-'a'] = i;
      dpr[i][M] = i == N ? INV : i;
      if (i < N) {
        for (int j = 0; j < M; j++) {
          int ni = next_char[t[j]-'a'];
          if (ni != -1) {
            int p = dpr[ni+1][j+1];

            if (p == -1) dpr[i][j] = -1;
            else dpr[i][j] = ni > i ? i : p;
          }
        }
      }
    }
  }

  int ans = 2e9;
  for (int split = 0; split <= N; split++) {
    for (int len1 = 0; len1 <= M; len1++) {
      int p1 = dpl[split][len1];
      int p2 = dpr[split][len1];

      if (p1 != -1 && p2 != -1) {
        int cost = 0;
        if (p2 != INV) cost += N - p2;
        if (p1 != INV) {
          cost++;
          cost += p1 + 1;
          cost += split - len1;
        }
        ckmin(ans, cost);
      }
    }
  }

  return (ans < 2e9 ? ans : -1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
