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

const int maxn = 2e5+5;
int N, M;
int par[maxn];
vector<int> adj[maxn];

vector<int> V;
int S[maxn];
bool blocked[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    par[b] = a;
  }
  FOR(i, 1, N+1) sort(all(adj[i]), greater());

  auto extend = [&]() -> void {
    while (true) {
      int i = V.back();
      if (!adj[i].empty()) {
        int j = adj[i].back();
        V.push_back(j);
        S[j] = 1;
      }
      else break;
    }
  };
  // initialize V, S
  V.push_back(1);
  S[1] = 1;
  extend();

  int ans = 0;
  REP(M) {
    int d; cin >> d;
    if (S[d]) ans++;
    else {
      vector<int> v;
      while (!S[d]) {
        if (blocked[d]) {
          cout << ans << '\n';
          return 0;
        }
        v.push_back(d);
        int nd = par[d];
        while (adj[nd].back() < d) {
          blocked[adj[nd].back()] = true;
          adj[nd].pop_back();
        }
        d = nd;
      }
      while (V.back() != d) {
        S[V.back()] = 0;
        V.pop_back();
      }
      reverse(all(v));
      for (auto i: v) {
        V.push_back(i);
        S[i] = 1;
      }
      extend();

      ans++;
    }
  }

  cout << ans << '\n';
}
