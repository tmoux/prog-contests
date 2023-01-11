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

const int maxn = 3e5+5;
int N, A[maxn];

const int maxp = 25000;
int spf[maxn];
int primeId[maxn], id = 0;
int toPrime[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    toPrime[id] = i;
    primeId[i] = id++;
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

vector<pair<int, int>> adj[maxp];
int dist[maxp];
pair<int, int> Prev[maxp];
bool term[maxp];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N;
  auto primes = [&](int x) -> vector<int> {
    vector<int> v;
    while (x > 1) {
      v.push_back(spf[x]);
      x /= spf[x];
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    return v;
  };
  FOR(i, 1, N + 1) {
    cin >> A[i];
    auto v = primes(A[i]);
    for (int a = 0; a < sz(v); a++) {
      for (int b = a + 1; b < sz(v); b++) {
        int x = primeId[v[a]];
        int y = primeId[v[b]];
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
      }
    }
  }

  int s, t; cin >> s >> t;
  if (s == t) {
    cout << 1 << '\n';
    cout << s << '\n';
    return 0;
  }
  else if (__gcd(A[s], A[t]) > 1) {
    cout << 2 << '\n';
    cout << s << ' ' << t << '\n';
    return 0;
  }

  auto v1 = primes(A[s]);
  queue<int> q;
  F0R(i, maxp) dist[i] = 1e9;
  F0R(i, maxp) Prev[i] = {-1, -1};
  for (auto p: v1) {
    q.push(primeId[p]);
    dist[primeId[p]] = 0;
  }

  auto v2 = primes(A[t]);
  for (auto p: v2) term[primeId[p]] = true;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    // cout << "visiting " << i << ": " << toPrime[i] << ' ' << dist[i] << endl;
    if (term[i]) {
      int d = dist[i];
      vector<int> ans;
      while (Prev[i].second != -1) {
        ans.push_back(Prev[i].second);
        i = Prev[i].first;
      }
      reverse(all(ans));

      cout << d+2 << '\n';
      cout << s << ' ';
      for (auto x: ans) {
        cout << x << ' ';
      }
      cout << t << '\n';
      return 0;
    }
    for (auto [j, id]: adj[i]) {
      if (dist[i] + 1 < dist[j]) {
        dist[j] = dist[i] + 1;
        Prev[j] = {i, id};
        q.push(j);
      }
    }
  }
  cout << -1 << '\n';
}
