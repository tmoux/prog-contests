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

const int maxn = 3005;
int N, M, Q;
vector<int> adj[maxn];
int dist[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  for (int i = 1; i <= M; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      dist[i][j] = maxn;
    }
  }
  for (int i = 1; i <= N; i++) {
    queue<int> q;
    dist[i][i] = 0;
    q.push(i);
    while (!q.empty()) {
      int f = q.front(); q.pop();
      for (int j: adj[f]) {
        if (dist[i][j] > dist[i][f] + 1) {
          dist[i][j] = dist[i][f] + 1;
          q.push(j);
        }
      }
    }
  }

  auto query = [&](int S, int T, int X, int U, int V, int Y) {
    if (dist[S][T] <= X || dist[U][V] <= Y) {
      return true;
    }
    else {
      X--;
      Y--;
      return dist[S][U] + dist[T][V] <= X + Y;
    }
  };

  cin >> Q;
  REP(Q) {
    int S, T, X, U, V, Y;
    cin >> S >> T >> X >> U >> V >> Y;
    bool poss = query(S, T, X, U, V, Y) 
             || query(S, T, X, V, U, Y);
    cout << (poss ? "YES" : "NO") << '\n';
  }
}

