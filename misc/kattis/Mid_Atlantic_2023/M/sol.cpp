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

int N;
string S;

const int maxn = 105;
int dp[maxn][26][26];
int D[maxn];

int f(int l, int r, int L, int R) {
  int& res = dp[l][L][R];
  if (res != -1) return res;
  if (l == r) {
    return res = 0;
  }
  else if (l + 1 == r) {
    if (L == R) return res = 0;
    else return res = 1;
  }
  else {
    res = 1e9;
    if (L == R) {
      ckmin(res, f(l+1, r-1, D[l+1], D[r-1]));
    }
    if (L != R) {
      F0R(LL, 26) {
        if (LL != D[l+1]) {
          ckmin(res, f(l+1, r-1, LL, D[r-1]) + 1);
        }
      }
      F0R(RR, 26) {
        if (RR != D[r-1]) {
          ckmin(res, f(l+1, r-1, D[l+1], RR) + 1);
          F0R(RR, 26) {
            if (RR != D[r-1]) {
              ckmin(res, f(l+1, r-1, D[l+1], RR) + 1);
            }
          }
        }
      }
    }
    F0R(LL, 26) {
      F0R(RR, 26) {
        if (LL != D[l+1] && RR != D[r-1])
          ckmin(res, f(l+1, r-1, LL, RR) + 2);
      }
    }
    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(dp, -1, sizeof dp);
  cin >> S;
  N = sz(S);
  F0R(i, N) D[i] = S[i] - 'a';

  int ans = f(0, N-1, D[0], D[N-1]);
  cout << ans << '\n';
}
