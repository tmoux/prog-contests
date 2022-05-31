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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K, Q; cin >> N >> K >> Q;
  vector<int> A(N);

  F0R(i, N) {
    cin >> A[i];
    A[i]--;
  }

  auto check_dag = [&](int l, int r) -> bool {
    vector<vector<int>> g(K);
    vector<int> deg(K, 0);
    for (int i = l; i <= r; i += 2) {
      if (i-1 >= l) {
        g[A[i]].push_back(A[i-1]);
        deg[A[i-1]]++;
      }
      if (i+1 <= r) {
        g[A[i]].push_back(A[i+1]);
        deg[A[i+1]]++;
      }
    }
    queue<int> q;
    F0R(i, K) if (deg[i] == 0) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
      int i = q.front(); q.pop();
      cnt++;
      for (int j: g[i]) {
        if (--deg[j] == 0) {
          q.push(j);
        }
      }
    }
    return cnt == K;
  };

  vector<int> maxr(N);
  F0R(i, N) {
    int r = i;
    for (int k = 11; k >= 0; k--) {
      int nr = r + (1<<k);
      if (nr < N && check_dag(i, nr)) {
        r = nr;
      }
    }
    maxr[i] = r;
  }

  REP(Q) {
    int x, y; cin >> x >> y;
    x--; y--;
    cout << (y <= maxr[x] ? "YES" : "NO") << '\n';
  }
}
