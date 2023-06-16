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
int N;
vector<int> adj[maxn];
int par[maxn];
double P[maxn];
double sum[maxn];
double ans = 0;

void dfs(int i, int p) {
  par[i] = p;
  if (i == 0) ans += P[i];
  else ans += P[i] * (1 - P[par[i]]);
  for (int j: adj[i]) {
    if (j == p) continue;
    sum[i] += P[j];
    dfs(j, i);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << fixed << setprecision(10);
  cin >> N;
  F0R(i, N) {
    string s; cin >> s;
    P[i] = 1 - stod(s);
  }
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(0, 0);
  int Q; cin >> Q;
  while (Q--) {
    int i; cin >> i;
    string s; cin >> s;
    double np = 1 - stod(s);
    if (i != 0) {
      int p = par[i];
      ans -= P[i] * (1 - P[p]);
      ans += np * (1 - P[p]);

      sum[p] -= P[i];
      sum[p] += np;
    }
    else {
      ans -= P[i];
      ans += np;
    }

    ans -= sum[i] * (1 - P[i]);
    ans += sum[i] * (1 - np);

    P[i] = np;

    cout << ans << '\n';
  }
}
