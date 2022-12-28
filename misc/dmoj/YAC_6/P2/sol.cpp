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

const int maxn = 1e6+6;
int N;
vector<int> s_adj[maxn];

int S[maxn], T[maxn];
int rt;

vector<pair<int, int>> ans;

void dfs_s(int i, int p) {
  for (int j: s_adj[i]) {
    dfs_s(j, i);
  }

  if (i != rt && T[i] != S[i]) {
    ans.push_back({i, T[i]});
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> S[i];
  }
  for (int i = 1; i <= N; i++) {
    cin >> T[i];
  }

  rt = 1;
  while (S[rt] != -1) rt++;
  if (T[rt] != -1) {
    cout << -1 << '\n';
    return 0;
  }
  for (int i = 1; i <= N; i++) {
    if (S[i] != -1) s_adj[S[i]].push_back(i);
  }

  dfs_s(rt, rt);
  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << a << ' ' << b << '\n';
  }
  return 0;
}
