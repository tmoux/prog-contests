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

const int maxn = 5e5+5;
int N;
vector<int> adj[maxn];

int mex(vector<int> v) {
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) if (v[i] != i) return i;
  return sz(v);
}

int G[maxn];
int grundy(int i) {
  int depth = adj[i].empty() ? 0 : 1e9;
  for (int j: adj[i]) {
    ckmin(depth, 1+grundy(j));
  }

  map<int, int> mp;
  queue<pair<int, int>> q;
  for (int j: adj[i]) {
    q.push({j, 1});
  }
  while (!q.empty()) {
    auto [f, d] = q.front(); q.pop();
    if (d <= depth+1) {
      mp[d] ^= G[f];
      for (auto j: adj[f]) {
        q.push({j, d+1});
      }
    }
  }

  vector<int> v;
  for (int i = 1; i <= depth+1; i++) {
    v.push_back(mp[i]);
  }
  G[i] = mex(v);
  // cout << i << ": " << G[i] << endl;
  return depth;
}

void solve() {
  memset(G, -1, sizeof G);
  cin >> N;
  FOR(i, 0, N+1) adj[i].clear();
  FOR(i, 1, N+1) {
    int p; cin >> p;
    adj[p].push_back(i);
  }
  int ans = 0;
  for (int i: adj[0]) {
    grundy(i);
    ans ^= G[i];
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
