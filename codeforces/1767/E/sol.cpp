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

const int maxn = 3e5+5, maxm = 45;
int N, M;

int color[maxn], cost[maxm];

int adj[maxm][maxm];

int dp1[1<<(maxm/2)];
int dp2[1<<(maxm/2)];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    cin >> color[i];
    --color[i];
  }
  // colors 0 .. M-1
  F0R(j, M) cin >> cost[j];
  F0R(i, N-1) {
    adj[color[i]][color[i+1]] = 1;
    adj[color[i+1]][color[i]] = 1;
  }

  int M2 = M / 2;
  F0R(mask, 1<<M2) {
    bool poss = true;
    F0R(i, M2) {
      F0R(j, M2) {
        if ((mask & (1<<i)) && (mask & (1<<j)) && adj[i][j]) {
          poss = false;
          break;
        }
      }
    }

    if (poss) {
      F0R(i, M2) if (mask & (1<<i)) {
        dp1[mask] += cost[i];
      }
    }
  }

  int M3 = M - M2;
  F0R(mask, 1<<M3) {
    bool poss = true;
    F0R(i, M3) {
      F0R(j, M3) {
        if ((mask & (1<<i)) && (mask & (1<<j)) && adj[i+M2][j+M2]) {
          poss = false;
          break;
        }
      }
    }

    if (poss) {
      F0R(i, M3) if (mask & (1<<i)) {
        dp2[mask] += cost[i+M2];
      }
    }
  }

  int c1 = color[0];
  int cn = color[N-1];

  const int INF = 1e9;
  F0R(mask, (1<<M3)) {
    if (c1 >= M2 && (mask & (1<<(c1-M2)))) dp2[mask] = -INF;
    if (cn >= M2 && (mask & (1<<(cn-M2)))) dp2[mask] = -INF;
  }

  F0R(mask, (1<<M2)) {
    if (c1 < M2 && (mask & (1<<c1))) dp1[mask] = -INF;
    if (cn < M2 && (mask & (1<<cn))) dp1[mask] = -INF;
  }

  F0R(i, M3) {
    F0R(mask, (1<<M3)) {
      if (mask & (1<<i)) {
        ckmax(dp2[mask], dp2[mask^(1<<i)]);
      }
    }
  }

  int ans = 0;

  F0R(mask, 1<<M2) {
    int all = (1<<M3) - 1;
    int mask2 = all;
    F0R(i, M2) if (mask & (1<<i)) {
      F0R(j, M3) if (adj[i][j+M2]) {
        mask2 &= (all ^ (1<<j));
      }
    }

    ckmax(ans, dp1[mask] + dp2[mask2]);
  }

  int total = 0;
  F0R(i, M) total += cost[i];
  cout << total - ans << '\n';
}
