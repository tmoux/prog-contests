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

const int maxn = 5005;
int N;
vector<int> adj[maxn];

ll dp[maxn][maxn];
ll upd[maxn];

int dfs(int i, int p) {
  int cur_sz = 1;
  for (int j: adj[i]) {
    if (j == p) continue;
    int b_sz = dfs(j, i);
    F0R(a, N+1) upd[a] = 0;
    for (int a = 0; a <= cur_sz; a++) {
      for (int b = 0; b <= b_sz && a + b <= N; b++) {
        // update dp[i][a+b]
        ll new_a = dp[i][a] + 1LL * b * (cur_sz-1); // increase edges by b
        ll new_b = dp[j][b] + 1LL * a * (b_sz-1); // increase edges by a
        ll new_edge = abs(a - b); // abs(b - ((a + b) - b));
        // ckmax(upd[a+b], dp[i][a] + dp[j][b] + abs(b - ((a+b) - b)));
        ckmax(upd[a+b], new_a + new_b + new_edge);
        // cout << "updating " << a << ' ' << b << ": " << upd[a+b] << ' ' << a+b << endl;
      }
    }
    cur_sz += b_sz;
    F0R(a, cur_sz+1) ckmax(dp[i][a], upd[a]);
  }
  DEBUG(i);
  FOR(j, 0, cur_sz+1) {
    cout << dp[i][j] << ' ';
  }
  cout << endl;
  return cur_sz;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 1);
  FOR(k, 0, N+1) {
    cout << dp[1][k] << " \n"[k == N];
  }
}
