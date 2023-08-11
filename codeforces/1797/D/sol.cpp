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

const int maxn = 1e5+5;
int N, M, A[maxn];
vector<int> g[maxn];
set<pair<int, int>> adj[maxn];
int par[maxn];

int cnt[maxn];
ll sum[maxn];

void dfs(int i, int p) {
  par[i] = p;
  cnt[i] = 1;
  sum[i] = A[i];
  for (int j: g[i]) {
    if (j == p) continue;
    dfs(j, i);
    adj[i].insert({cnt[j], -j});
    cnt[i] += cnt[j];
    sum[i] += sum[j];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> A[i];
  }
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(1, 0);

  while (M--) {
    int t, x; cin >> t >> x;
    if (t == 1) {
      cout << sum[x] << '\n';
    }
    else {
      if (adj[x].empty()) continue;
      else {
        auto [_, j] = *adj[x].rbegin();
        j = -j;
        adj[x].erase(prev(adj[x].end()));

        int p = par[x];
        adj[p].erase({cnt[x], -x});

        sum[x] -= sum[j];
        sum[j] += sum[x];

        cnt[x] -= cnt[j];
        cnt[j] += cnt[x];

        adj[p].insert({cnt[j], -j});
        adj[j].insert({cnt[x], -x});

        par[j] = p;
        par[x] = j;
      }
    }
  }
}
