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

ll solve() {
  int N; cin >> N;
  vector<int> g(N);
  vector<vector<int>> gr(N);
  vector<int> indegree(N);
  F0R(i, N) {
    cin >> g[i];
    g[i] += i;
    if (0 <= g[i] && g[i] < N) {
      gr[g[i]].push_back(i);
      indegree[i]++;
    }
  }

  vector<bool> isTerm(N, false), isOnPath(N, false);
  vector<int> preds(N); // including itself
  queue<int> q;
  F0R(i, N) {
    if (indegree[i] == 0) q.push(i);
  }
  int numTerm = 0;
  auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
    isTerm[i] = true;
    numTerm++;
    preds[i] = 1;
    for (int j: gr[i]) {
      if (j != p) {
        dfs(j, i);
        preds[i] += preds[j];
      }
    }
  });
  while (!q.empty()) {
    int i = q.front(); q.pop();
    dfs(i, i);
  }

  {
    int i = 0;
    REP(N) {
      isOnPath[i] = true;
      i = g[i];
      if (i < 0 || i >= N) break;
    }
  }

  ll ans = 0;
  F0R(i, N) {
    if (!isOnPath[i]) {
      if (isTerm[0]) {
        ans += 2*N + 1;
      }
      else {
        ans += 0;
      }
    }
    else {
      if (isTerm[0]) {
        ans += numTerm - preds[i] + (N + 1);
      }
      else {
        ans += numTerm + (N + 1);
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}