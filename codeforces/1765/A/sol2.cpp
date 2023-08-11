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

namespace flow {
  const int inf = 1e9;

  int n;
  vector<vector<int>> capacity, flow;
  vector<int> height, excess;

  void init(int _n) {
    n = _n;
    capacity = vector<vector<int>>(n, vector<int>(n, 0));
  }

  void add_edge(int u, int v, int c) {
    capacity[u][v] = c;
  }

  void push(int u, int v)
  {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
  }

  void relabel(int u)
  {
    int d = inf;
    for (int i = 0; i < n; i++) {
      if (capacity[u][i] - flow[u][i] > 0)
        d = min(d, height[i]);
    }
    if (d < inf)
      height[u] = d + 1;
  }

  vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < n; i++) {
      if (i != s && i != t && excess[i] > 0) {
        if (!max_height.empty() && height[i] > height[max_height[0]])
          max_height.clear();
        if (max_height.empty() || height[i] == height[max_height[0]])
          max_height.push_back(i);
      }
    }
    return max_height;
  }

  int max_flow(int s, int t)
  {
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++) {
      if (i != s)
        push(s, i);
    }

    vector<int> current;
    while (!(current = find_max_height_vertices(s, t)).empty()) {
      for (int i : current) {
        bool pushed = false;
        for (int j = 0; j < n && excess[i]; j++) {
          if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
            push(i, j);
            pushed = true;
          }
        }
        if (!pushed) {
          relabel(i);
          break;
        }
      }
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
      max_flow += flow[i][t];
    return max_flow;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<bool>> G(N, vector<bool>(M));
  F0R(i, N) {
    string s; cin >> s;
    for (int j = 0; j < M; j++) {
      G[i][j] = s[j] - '0';
    }
  }
  const int maxn = 505;
  vector<bitset<maxn>> bs(M);
  F0R(j, M) {
    F0R(i, N) {
      if (G[i][j]) bs[j][i] = 1;
    }
  }
  flow::init(2 * M + 2);
  int source = 2 * M;
  int sink = 2 * M + 1;
  F0R(i, M) {
    flow::add_edge(source, i, 1);
    flow::add_edge(i + M, sink, 1);
  }


  vector<bool> ignore(M, false);
  vector<int> sameAs(M);
  // If two documents are at same level, merge them
  int numIgnore = 0;
  F0R(i, M) if (!ignore[i]) {
    for (int j = i+1; j < M; j++) {
      if (bs[i] == bs[j]) {
        ignore[j] = true;
        sameAs[j] = i;
        numIgnore++;
      }
    }
  }
  F0R(i, M) {
    if (ignore[i]) continue;
    F0R(j, M) {
      if (ignore[j]) continue;
      if (i != j) {
        if (bs[i] == bs[j]) {
          ignore[j] = true;
          sameAs[j] = i;
          numIgnore++;
        }
        else if (bs[i] == (bs[i] & bs[j])) {
          flow::add_edge(i, j + M, 1);
        }
      }
    }
  }

  int f = flow::max_flow(source, sink);
  int chains = M - f - numIgnore;

  vector<int> next(M, -1);
  vector<int> cnt(M, 0);
  F0R(i, M) {
    F0R(j, M) {
      if (ignore[i] || ignore[j]) continue;
      if (flow::flow[i][j+M] == 1) {
        next[i] = j;
        cnt[j]++;
      }
    }
  }

  vector<int> accessGroup(M);
  vector<int> accessLevel(M);
  int curGroup = 1;
  vector<vector<int>> devLevel(N, vector<int>(1000 + 1, 1));
  F0R(i, M) if (!ignore[i] && cnt[i] == 0) {
    assert(curGroup <= chains);
    int j = i;
    int level = 100000;
    bitset<maxn> cur;
    while (j != -1) {
      F0R(k, N) {
        if (!cur[k] && bs[j][k]) {
          devLevel[k][curGroup] = level;
        }
      }
      accessGroup[j] = curGroup;
      accessLevel[j] = level;

      cur = bs[j];
      j = next[j];
      level--;
    }
    curGroup++;
  }

  cout << chains << '\n';
  F0R(i, M) {
    cout << (!ignore[i] ? accessGroup[i] : accessGroup[sameAs[i]]) << ' ';
  }
  cout << '\n';
  F0R(i, M) {
    cout << (!ignore[i] ? accessLevel[i] : accessLevel[sameAs[i]]) << ' ';
  }
  cout << '\n';
  F0R(i, N) {
    for (int j = 1; j <= chains; j++) {
      cout << devLevel[i][j] << ' ';
    }
    cout << '\n';
  }
}
