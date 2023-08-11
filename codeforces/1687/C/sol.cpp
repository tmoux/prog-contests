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

bool solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N+1), B(N+1);
  FOR(i, 1, N+1) cin >> A[i];
  FOR(i, 1, N+1) cin >> B[i];
  vector<ll> C(N+1);
  FOR(i, 1, N+1) {
    C[i] = A[i] - B[i] + C[i-1];
  }
  vector<vector<pair<int, int>>> to(N+1);
  F0R(i, M) {
    int l, r; cin >> l >> r;
    to[l-1].push_back({r, i});
    to[r].push_back({l-1, r});
  }
  set<int> s;
  FOR(i, 1, N+1) {
    if (C[i]) s.insert(i);
  }

  queue<pair<int, int>> q;
  FOR(i, 1, N+1) {
    if (C[i] == 0) {
      for (auto [j, id]: to[i]) {
        if (!C[j]) {
          q.push({min(i, j), max(i, j)});
        }
      }
    }
  }
  while (!q.empty()) {
    auto [l, r] = q.front(); q.pop();
    vector<int> rem;
    for (auto it = s.lower_bound(l); it != s.end() && *it <= r; ++it) {
      rem.push_back(*it);
      for (auto [j, id]: to[*it]) {
        if (!s.count(j)) {
          q.push({min(*it, j), max(*it, j)});
        }
      }
    }
    for (auto i: rem) s.erase(i);
  }

  return s.empty();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "YES" : "NO") << '\n';
  }
}
