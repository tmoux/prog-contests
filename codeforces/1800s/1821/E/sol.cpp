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

const int maxn = 2e5+1;
map<array<int, 4>, int> toIdx;
array<int, 4> fromIdx[130];
const ll INF = LLONG_MAX;

string S;
int N, K;
ll dp[maxn][130];
int bal[maxn];

ll f(int i, int s) {
  auto& res = dp[i][s];
  if (res != -1) return res;

  auto [c1, c2, d1, d2] = fromIdx[s];
  int k = c1 + c2;
  int curBal = i == 0 ? 0 : bal[i-1];
  curBal -= c1 - d1;
  curBal += c2 - d2;
  if (curBal < 0) return res = INF;

  // cout << i << ' ' << c1 << ' ' << c2 << ' ' << d1 << ' ' << d2 << ": " << curBal << endl;

  // Base case: i = n, and put down all
  if (i == N && c1 == d1 && c2 == d2) {
    return res = 0;
  }

  res = INF;
  // take current one
  if (i < N) {
    ll cur = S[i] == '(' ? curBal : 0;
    ckmin(res, f(i+1, s) + cur);

    // pickup
    if (k < K) {
      if (S[i] == '(') {
        int ns = toIdx[{c1+1, c2, d1, d2}];
        ckmin(res, f(i+1, ns));
      }
      else {
        int ns = toIdx[{c1, c2+1, d1, d2}];
        ckmin(res, f(i+1, ns));
      }
    }
  }

  // putdown
  if (d1 < c1) {
    int ns = toIdx[{c1, c2, d1+1, d2}];
    ckmin(res, f(i, ns) + curBal);
  }
  if (d2 < c2) {
    int ns = toIdx[{c1, c2, d1, d2+1}];
    ckmin(res, f(i, ns));
  }

  return res;
}

void solve() {
  cin >> K >> S;
  N = sz(S);
  F0R(i, N) {
    bal[i] = S[i] == '(' ? 1 : -1;
    if (i > 0) bal[i] += bal[i-1];
  }
  F0R(i, N+1) F0R(j, 130) dp[i][j] = -1;
  cout << f(0, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int idx = 0;
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; i+j <= 5; j++) {
      for (int a = 0; a <= i; a++) {
        for (int b = 0; b <= j; b++) {
          fromIdx[idx] = {i, j, a, b};
          toIdx[{i, j, a, b}] = idx++;
        }
      }
    }
  }
  int T; cin >> T;
  while (T--) solve();
}
