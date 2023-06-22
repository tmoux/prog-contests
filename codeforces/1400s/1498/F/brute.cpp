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
int N, K, A[maxn];

vector<int> adj[maxn];

struct T {
  vector<array<int, 2>> v;
  T() {
    v.resize(K, {0, 0});
  }

  T extend() {
    T r = T();
    F0R(i, K-1) {
      r.v[i] = v[i+1];
    }
    r.v[K-1] = {v[0][1], v[0][0]};
    return r;
  }

  int getans() {
    int res = 0;
    F0R(i, K) res ^= v[i][1];
    return res != 0;
  }
};

T merge(T a, T b) {
  F0R(i, K) {
    F0R(j, 2) {
      a.v[i][j] ^= b.v[i][j];
    }
  }
  return a;
}

T F[maxn];
void dfs(int i, int p) {
  F[i] = T();
  F[i].v[0][0] = A[i];

  for (auto j: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    F[i] = merge(F[i], F[j].extend());
  }
}

int ans[maxn];
void reroot(int i, int p, T cur) {
  // cout << "vis " << i << ' ' << p << endl;
  T r = merge(F[i], cur.extend());
  // cout << i << ": " << r.v << endl;
  // cout << cur.extend().v << endl;
  ans[i] = r.getans();

  for (int j: adj[i]) {
    if (j == p) continue;
    T ncur = merge(r, F[j].extend());
    // cout << i << ' ' << j << ": " << ncur.v << endl;
    reroot(j, i, ncur);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N-1) {
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  FOR(i, 1, N+1) cin >> A[i];

  // dfs(1, 1);

  // // FOR(i, 1, N+1) {
  // //   cout << i << ": " << F[i].v << endl;
  // // }
  // reroot(1, 1, T());

  FOR(i, 1, N+1) {
    dfs(i, i);
    cout << F[i].getans() << " \n"[i == N];
  }
}
