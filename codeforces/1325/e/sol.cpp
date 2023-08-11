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

const int maxx = 1e6+5;
int spf[maxx];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxx; i++) if (!spf[i]) {
    for (int j = i; j < maxx; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

const int maxn = 1e5+5;
int N, A[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N;
  vector<int> primes = {1};
  map<pair<int, int>, int> edges;
  F0R(i, N) {
    cin >> A[i];
    map<int, int> mp;
    while (A[i] > 1) {
      mp[spf[A[i]]]++;
      A[i] /= spf[A[i]];
    }
    vector<int> v;
    for (auto [p, c]: mp) {
      if (c&1) v.push_back(p);
    }
    if (v.empty()) {
      cout << 1 << '\n';
      return 0;
    }
    else {
      for (auto p: v) primes.push_back(p);
      if (sz(v) == 1) {
        edges[{1, v[0]}]++;
      }
      else {
        edges[{v[0], v[1]}]++;
      }
    }
  }
  sort(all(primes)); primes.erase(unique(all(primes)), primes.end());
  vector<vector<int>> adj(maxx);
  for (auto [p, c]: edges) {
    if (c > 1) {
      cout << 2 << '\n';
      return 0;
    }
    else {
      auto [u, v] = p;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  const int INF = 1e9;
  vector<int> dist(maxx, INF), prev(maxx, -1);
  int ans = INF;
  for (auto i: primes) {
    if (1LL*i*i > maxx) continue;
    for (auto p: primes) {
      dist[p] = INF;
      prev[p] = -1;
    }
    queue<int> q;
    dist[i] = 0;
    q.push(i);
    while (!q.empty()) {
      int f = q.front(); q.pop();
      for (int j: adj[f]) {
        if (dist[j] > dist[f] + 1) {
          dist[j] = dist[f] + 1;
          prev[j] = f;
          q.push(j);
        }
        else if (prev[f] != j && prev[j] != f) {
          ckmin(ans, dist[j] + dist[f] + 1);
        }
      }
    }
  }

  cout << (ans < INF ? ans : -1) << '\n';
}
