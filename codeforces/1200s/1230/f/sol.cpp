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

// Let's split up vertices into "small" and "big" vertices, which have degree < K and >= K, respectively.
// For small vertices, let's just manually update all of their edges.
// For big vertices, there are only up to M / K of them, so let's process each one in O(Q) amortized.
// Keep track of the last time the big vertex has been updated, and update all of the adjacent vertices that have been updated since then.

const int maxn = 1e5+5;
int N, M, A[maxn];
vector<int> adj[maxn];

int in[maxn], out[maxn];
ll ans = 0;

ll cnt(int i) {
  return 1LL * in[i] * out[i];
}

void fix(int i, int j) {
  if (A[i] < A[j]) {
    ans -= cnt(i);
    ans -= cnt(j);

    in[i]--, out[i]++;
    out[j]--, in[j]++;

    ans += cnt(i);
    ans += cnt(j);
  }
}

int last[maxn];
int q[maxn];

vector<bool> isadj[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) A[i] = i;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  FOR(i, 1, N+1) {
    for (int j: adj[i]) {
      if (A[i] > A[j]) out[i]++;
      else in[i]++;
    }
    ans += cnt(i);
  }

  cout << ans << '\n';
  memset(last, -1, sizeof last);
  const int K = 500;
  FOR(i, 1, N+1) {
    if (sz(adj[i]) >= K) {
      isadj[i].resize(N+1, 0);
      for (int j: adj[i]) isadj[i][j] = 1;
    }
  }
  int Q; cin >> Q;
  vector<bool> seen(N+1, 0);
  F0R(i, Q) {
    int v; cin >> v;
    q[i] = v;
    if (sz(adj[v]) < K || last[v] == -1) {
      for (int j: adj[v]) {
        fix(v, j);
      }
    }
    else {
      for (int t = last[v]+1; t < i; t++) {
        int j = q[t];
        if (!seen[j] && isadj[v][j]) {
          seen[j] = 1;
          fix(v, j);
        }
      }
      for (int t = last[v]+1; t < i; t++) {
        seen[q[t]] = 0;
      }
    }
    last[v] = i;
    A[v] = N + 1 + i;
    cout << ans << '\n';
  }
}
