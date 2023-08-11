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

int N, M, Q;
const int maxn = 1e5+5;
vector<pair<int, int>> adj[maxn];

int ans[maxn];

int approx(int t) {
  vector<int> dist(N, 1e9);
  queue<int> q;
  q.push(0);
  dist[0] = 0;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    for (auto [j, tt]: adj[i]) if (tt < t) {
      if (dist[j] > dist[i] + 1) {
        dist[j] = dist[i] + 1;
        q.push(j);
      }
    }
  }
  return *max_element(all(dist));
}

// l       v     r
// T T T T F F F F
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> Q;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].emplace_back(b, -1);
    adj[b].emplace_back(a, -1);
  }
  F0R(i, Q) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].emplace_back(b, i);
    adj[b].emplace_back(a, i);
  }

  ans[0] = approx(0);
  int x = ans[0];
  int i = 0;

  while (true) {
    int ni = find_first_false(i, Q+1, [&](int t) { return 2 * approx(t) >= x; });
    for (int j = i; j < ni; j++) ans[j] = x;
    if (ni <= Q) {
      x = approx(ni);
      i = ni;
    }
    else break;
  }

  F0R(i, Q+1) {
    cout << ans[i] << " \n"[i == Q];
  }
}
