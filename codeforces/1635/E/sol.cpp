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
int N, M;

vector<pair<int, int>> adj[maxn];
vector<int> g[maxn];

bool poss = true;
int color[maxn];
void dfs(int i, int c) {
  color[i] = c;
  for (auto [j, t]: adj[i]) {
    if (color[j] == c) {
      poss = false;
    }
    else if (color[j] == -1) {
      dfs(j, c^1);
    }
  }
}

int indegree[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  REP(M) {
    int t, i, j; cin >> t >> i >> j;
    adj[i].push_back({j, t});
    adj[j].push_back({i, t});
  }

  memset(color, -1, sizeof color);
  FOR(i, 1, N+1) {
    if (color[i] == -1) {
      dfs(i, 0);
    }
  }

  if (!poss) {
    cout << "NO\n";
    return 0;
  }

  FOR(i, 1, N+1) {
    for (auto [j, t]: adj[i]) {
      if (color[i] == 0 && t == 2) {
        g[i].push_back(j);
        indegree[j]++;
      }
      else if (color[i] == 1 && t == 1) {
        g[i].push_back(j);
        indegree[j]++;
      }
    }
  }

  vector<int> order(N+1);
  queue<int> q;
  FOR(i, 1, N+1) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  int cnt = 0;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    order[i] = cnt++;
    for (int j: g[i]) {
      if (--indegree[j] == 0) {
        q.push(j);
      }
    }
  }

  if (cnt == N) {
    cout << "YES\n";
    FOR(i, 1, N+1) {
      cout << (color[i] ? 'L' : 'R') << ' ' << order[i] << '\n';
    }
  }
  else {
    cout << "NO\n";
  }
}
