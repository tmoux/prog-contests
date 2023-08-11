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

const int maxn = 1e5+5, maxk = 30;
int N, Q;

bool is_zero[maxn];
vector<int> adj[maxn];

int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;

  vector<array<int, 3>> constraints;
  while (Q--) {
    int i, j, x; cin >> i >> j >> x;
    constraints.push_back({i, j, x});
  }

  F0R(k, maxk) {
    for (int i = 1; i <= N; i++) {
      is_zero[i] = false;
      adj[i].clear();
    }
    for (auto [i, j, x]: constraints) {
      if (x & (1<<k)) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
      else {
        is_zero[i] = is_zero[j] = true;
      }
    }

    vector<int> mark(N+1, 0);
    for (int i = 1; i <= N; i++) {
      bool can_be_zero = is_zero[i];
      if (!can_be_zero) {
        can_be_zero = true;
        for (int j: adj[i]) {
          can_be_zero &= ((j < i && mark[j] == 1) || (j > i && !is_zero[j]));
          if (!can_be_zero) break;
        }
      }
      mark[i] = can_be_zero ? 0 : 1;
    }

    for (int i = 1; i <= N; i++) {
      ans[i] += mark[i] << k;
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
