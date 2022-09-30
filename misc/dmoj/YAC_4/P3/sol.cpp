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
int N, M, B;

vector<int> adj[maxn];

bool is_bipartite = true;
bool vis[maxn];
int depth[maxn];
int ans[maxn];

vector<int> gr[maxn];
void dfs(int i) {
  ans[i] = depth[i]&1 ? B : 0;
  vis[i] = true;
  for (int j: adj[i]) {
    if (vis[j]) {
      if ((depth[i] - depth[j]) % 2 == 0) {
        // odd cycle
        is_bipartite = false;
        gr[i].push_back(j);
        gr[j].push_back(i);
      }
    }
    else {
      depth[j] = depth[i] + 1;
      dfs(j);
    }
  }
}

int X, Y, Z, W;

void color(int i, int p) {
  vis[i] = true;
  if (depth[i]&1) {
    if (i == p || ans[p] == Y) {
      ans[i] = X;
    }
    else ans[i] = Y;
  }
  else {
    if (i == p || ans[p] == W) {
      ans[i] = Z;
    }
    else ans[i] = W;
  }
  for (int j: gr[i]) if (j != p) {
    color(j, i);
  }
}

int try_color() {
  for (int i = 1; i <= N; i++) vis[i] = false;
  for (int i = 1; i <= N; i++) {
    if (!vis[i]) {
      color(i, i);
    }
  }
  int mx = 0;
  for (int i = 1; i <= N; i++) {
    ckmax(mx, ans[i]);
  }
  return mx;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> B;
  // subtask 3

  REP(M) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1);

  int max_beauty;
  if (!is_bipartite) {
    int z = 1;
    while ((z << 1) <= B) z <<= 1;
    z--;

    X = B;
    Y = X ^ z;
    Z = 0;
    W = Z ^ z;
    max_beauty = z;

    if (try_color() <= B) {
      goto done;
    }
    else {
      swap(X, Z);
      swap(Y, W);
      if (try_color() <= B) {
        goto done;
      }
      else {
        swap(X, Z);
        swap(Y, W);

        X = z;
        z >>= 1;
        Y = X ^ z;
        Z = 0;
        W = Z ^ z;
        max_beauty = z;

        int mx = try_color();
        assert(mx <= B);
      }
    }
  }
  else {
    max_beauty = B;
  }

  done:
  // output
  cout << max_beauty << '\n';
  for (int i = 1; i <= N; i++) {
    cout << ans[i] << " \n"[i == N];
  }
}
