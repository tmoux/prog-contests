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

const int maxn = 2e5+5;
int N;
vector<int> adj[maxn];
int ans[maxn];

const int B = 450;
vector<pair<int, int>> small[maxn];
vector<pair<int, int>> big[maxn];

vector<int> dfs(int i, int p) {
  vector<int> v(B);
  for (int j: adj[i]) {
    if (j == p) continue;
    auto u = dfs(j, i);
    F0R(k, B) v[k] += u[k];
  }

  for (auto [k, id]: small[i]) {
    ans[id] = v[k];
  }

  F0R(k, B) v[k] = max(1, -k + v[k]);
  return v;
}

int sub_size[maxn];
int f[maxn][B+2];

int g[B+5];
void dfs2(int i, int p) {
  memset(f[i], -0x3f, sizeof(f[i]));
  memset(g, -0x3f, sizeof(g));
  sub_size[i] = 1;
  f[i][0] = 0;
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs2(j, i);
    for (int a = 0; a <= min(sub_size[i], B); a++) {
      for (int b = 0; b <= sub_size[j] && a+b <= B; b++) {
        ckmax(g[a+b], f[i][a] + 1);
        ckmax(g[a+b+1], dp[a] + dp[b]);
      }
    }

    sub_size[i] += sub_size[j];
    for (int a = 0; a <= min(sub_size[i], B); a++) {
      dp[a] = f[a];
    }
    fill(f, f+B+5, -1e9);
  }

  for (auto [k, id]: big[i]) {
    F0R(j, B+1) {
      ckmax(ans[id], -k * j + dp[j]);
    }
  }
  return dp;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  REP(N-1) {
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  memset(ans, -1, sizeof ans);

  int Q; cin >> Q;
  F0R(i, Q) {
    int v, k; cin >> v >> k;
    if (k < B) {
      small[v].push_back({k, i});
    }
    else {
      big[v].push_back({k, i});
    }
  }

  dfs(1, 1);
  dfs2(1, 1);

  F0R(i, Q) cout << ans[i] << '\n';
}
