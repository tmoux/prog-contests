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
  const int MOD = 998244353;
  auto madd = [&](int& a, int b) {
    ll c = a + b;
    a = c % MOD;
  };
  int N, M; cin >> N >> M;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }

  vector<vector<int>> adj(N);
  vector<int> indegree(N);
  F0R(i, M) {
    int x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y);
    indegree[y]++;
  }

  vector<int> order;
  queue<int> q;
  F0R(i, N) if (!indegree[i]) q.push(i);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    order.push_back(i);
    for (int j: adj[i]) if (--indegree[j] == 0) q.push(j);
  }
  int sink = order.back();

  reverse(all(order));
  for (int iter = 0; iter < N; iter++) {
    if (all_of(all(A), [](auto x) { return x == 0; })) {
      return iter;
    }
    for (int i: order) {
      if (A[i] > 0) {
        A[i]--;
        for (int j: adj[i]) A[j]++;
      }
    }
  }

  reverse(all(order));
  for (int i: order) {
    for (int j: adj[i]) {
      madd(A[j], A[i]);
    }
  }
  int ans = A[sink];
  madd(ans, N);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
