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

void solve() {
  int N; cin >> N;
  vector<int> b(N+1);
  int k = 0;
  vector<vector<int>> adj(N+1);
  vector<int> degree(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> b[i];
    ckmax(k, min(i, b[i]));
    if (1 <= b[i] && b[i] <= N) {
      adj[b[i]].push_back(i);
      degree[i]++;
    }
  }

  vector<int> queue;
  for (int i = 1; i <= N; i++) {
    if (degree[i] == 0) queue.push_back(i);
  }

  vector<int> a;
  while (!queue.empty()) {
    int last = 0;
    for (int i = 1; i < sz(queue); i++) {
      if (!adj[queue[i]].empty()) {
        last = i;
      }
    }

    for (int i = 0; i < sz(queue); i++) {
      if (i != last) a.push_back(queue[i]);
    }
    a.push_back(queue[last]);

    vector<int> nqueue;
    for (int x: queue) {
      for (int y: adj[x]) {
        if (--degree[y] == 0) nqueue.push_back(y);
      }
    }
    queue = nqueue;
  }

  cout << k << '\n';
  for (int x: a) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
