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
  int N; cin >> N;
  vector<vector<int>> adj(N+1);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> v;
  y_combinator([&](auto dfs, int i, int p) -> void {
    v.push_back(i);
    for (int j: adj[i]) {
      if (j == p) continue;
      dfs(j, i);
      v.push_back(i);
    }
  })(1, 1);

  auto query = [&](vector<int> v) {
    sort(all(v)); v.erase(unique(all(v)), v.end());
    cout << "? ";
    cout << sz(v) << ' ';
    for (auto i: v) cout << i << ' ';
    cout << endl;
    int x; cin >> x;
    return x;
  };

  int mx = query(v);
  int lo = 0, hi = sz(v)-1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    vector<int> V;
    for (int i = lo; i <= mid; i++) V.push_back(v[i]);
    int x = query(V);
    if (x == mx) hi = mid;
    else lo = mid;
  }
  cout << "! " << v[lo] << ' ' << v[lo+1] << endl;
}
