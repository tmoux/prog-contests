#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

/*
** For each pair (x, y), build a "center" node with weights of 0 connecting to each index
** Run dijkstra from each center to get distances to/from a center. (Actually just use 0-1 BFS)
** For each query (s -> t), either s goes to t directly, or s goes to some center node. We can just iterate over all centers.
 */
const int maxn = 50005;
string S;
int N, Q;

int centerIndex(int x, int y) {
  return N + x * 26 + y;
}
vector<pair<int, int>> adj[maxn + 2*26*26];

int dist[26*26][maxn+2*26*26];

vector<int> vs[maxn + 26*26];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> S;
  // REP(50000) {
  //   char c = rng() % 26 + 'a';
  //   S += c;
  // }
  N = sz(S);

  F0R(i, N - 1) {
    int x = S[i] - 'a', y = S[i+1] - 'a';
    vs[centerIndex(x, y)].push_back(i);
    adj[i].emplace_back(i+1, 1);
    adj[i+1].emplace_back(i, 1);
  }
  for (int c = N; c < N+26*26; c++) {
    for (auto i: vs[c]) {
      // adj[c].emplace_back(i, 0);
      adj[i].emplace_back(c, 1);
      adj[c].emplace_back(i, 0);
    }
  }
  // Run BFS from each center
  F0R(c, 26*26) {
    F0R(i, N+2*26*26) dist[c][i] = 1e9;
    dist[c][N+c] = 0;
    deque<int> deq; deq.push_back(N+c);
    while (!deq.empty()) {
      int i = deq.front(); deq.pop_front();
      for (auto [j, w]: adj[i]) {
        if (dist[c][j] > dist[c][i] + w) {
          dist[c][j] = dist[c][i] + w;
          if (w == 0) deq.push_front(j);
          else deq.push_back(j);
        }
      }
    }
  }

  cin >> Q;
  while (Q--) {
    int s, t; cin >> s >> t;
    s--, t--;

    int ans = abs(s - t);
    F0R(c, 26*26) {
      ckmin(ans, dist[c][s] + dist[c][t] + 1);
    }
    cout << ans << '\n';
  }
}
