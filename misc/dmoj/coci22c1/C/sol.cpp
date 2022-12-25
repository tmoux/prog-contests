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
const double eps = 1e-6;
int N, M;
vector<int> adj[maxn];

double X[maxn], Y[maxn];

double dist(int i, int j) {
  return hypot(X[i] - X[j], Y[i] - Y[j]);
}

bool vis[maxn];
vector<double> dists;
vector<int> cyc;
void dfs(int i) {
  vis[i] = true;
  cyc.push_back(i);
  for (int j: adj[i]) if (!vis[j]) {
    dists.push_back(dist(i, j));
    dfs(j);
  }
}

double mindist[maxn];

double ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    cin >> X[i] >> Y[i];
  }
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  F0R(i, N) {
    mindist[i] = 1e9;
    for (int j: adj[i]) {
      ckmin(mindist[i], dist(i, j));
    }
  }

  int comps = 0;
  F0R(i, N) {
    if (!vis[i]) {
      dfs(i);
      comps++;
    }
  }
  
  dfs(0);
  cyc.pop_back();
  dists.push_back(dist(cyc[0], cyc.back()));
  assert(sz(dists) == N);
  double r = 0;
  F0R(i, sz(dists)) {
    if (i % 2 == 0) r += dists[i];
    else r -= dists[i];
  }
  r /= 2;

  ans[0] = r;
  for (int i = 1; i < N; i++) {
    ans[cyc[i]] = dists[i-1] - ans[cyc[i-1]];
  }

  bool poss = true;
  F0R(i, N) {
    if (ans[i] > mindist[i] + eps) poss = false;
  }

  if (!poss) {
    cout << "NE\n";
  }
  else {
    cout << "DA\n";
    F0R(i, N) {
      cout << fixed << setprecision(10) << ans[i] << '\n';
    }
  }
}
