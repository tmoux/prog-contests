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

const int maxn = 20;
int N, M;
int adj[maxn][maxn];
int adj_mask[1 << maxn];
int start[1 << maxn];

int dp[maxn][1 << maxn];

void recon(int i, int mask, vector<int>& v) {
  v.push_back(i);
  if (i != start[mask]) {
    int j = dp[i][mask];
    recon(j, mask ^ (1 << i), v);
  }
}

int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a][b] = adj[b][a] = 1;
  }

  F0R(mask, 1 << N) {
    F0R(i, N) {
      if (mask & (1 << i)) {
        F0R(j, N) {
          if (adj[i][j]) {
            adj_mask[mask] |= 1 << j;
          }
        }
      }
    }
    if (mask > 0) {
      F0R(i, N) {
        if (mask & (1 << i)) {
          start[mask] = i;
          break;
        }
      }
    }
  }

  auto finish = [&](const vector<int>& v) {
    queue<int> q;
    memset(ans, -1, sizeof ans);
    F0R(k, sz(v)) {
      ans[v[k]] = v[(k+1)%sz(v)];
      q.push(v[k]);
    }
    while (!q.empty()) {
      int x = q.front(); q.pop();
      F0R(y, N) if (adj[x][y] && ans[y] == -1) {
        ans[y] = x;
        q.push(y);
      }
    }
    cout << "Yes\n";
    F0R(k, N) {
      cout << ans[k]+1 << ' ';
    }
    cout << '\n';
  };

  queue<pair<int, int>> q;
  F0R(i, N) {
    q.emplace(i, 1 << i);
  }
  memset(dp, -1, sizeof dp);
  while (!q.empty()) {
    auto [i, mask] = q.front(); q.pop();

    int s = start[mask];
    if (adj[i][s] && adj_mask[mask] == ((1 << N) - 1)) {
      // found valid cycle
      vector<int> v;
      recon(i, mask, v);

      finish(v);
      return 0;
    }

    FOR(j, s+1, N) {
      if (!(mask & (1 << j)) && adj[i][j] && dp[j][mask | (1 << j)] == -1) {
        dp[j][mask | (1 << j)] = i;
        q.emplace(j, mask | (1 << j));
      }
    }
  }

  cout << "No\n";
}
