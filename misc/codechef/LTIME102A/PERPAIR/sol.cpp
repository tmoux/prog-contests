#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

// }}}

const int maxn = 20;
int fac[maxn], ifac[maxn];

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int comb(int n, int k) {
  if (n < k) return 0;
  int ans = fac[n];
  ans = mult(ans, ifac[k]);
  ans = mult(ans, ifac[n-k]);
  return ans;
}

int dp[maxn][maxn];

int brute(int N, int K) {
  if (dp[N][K] != -1) return dp[N][K];
  vector<int> p;
  for (int i = 0; i < N; i++) p.push_back(i);
  int ans = 0;
  do {
    for (int i = 0; i < N; i++) {
      for (int j = i+K+1; j < N; j++) {
        if (p[i] < p[j]) {
          bool poss = true;
          for (int k = 0; k < i; k++) {
            if (p[k] > p[i]) {
              poss = false;
              break;
            }
          }
          for (int k = i+1; k < j; k++) {
            if (p[k] > p[i]) {
              poss = false;
              break;
            }
          }
          if (poss) ans++;
        }
      }
    }
  } while (next_permutation(all(p)));
  return dp[N][K] = ans;
}

int solve(int N, int K) {
  int ans = 0;
  for (int i = K; i <= N-2; i++) {
    for (int ex = 0; ex+K <= i; ex++) {
      int add = comb(i, ex+K);
      add = mult(add, fac[ex+K]);
      add = mult(add, N-1-i);
      add = mult(add, fac[N-(ex+K+2)]);

      madd(ans, add);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fac[i] = mult(fac[i-1], i);
    ifac[i] = inverse(fac[i]);
  }
  memset(dp, -1, sizeof dp);
  int T; cin >> T;
  while (T--) {
    int N, K; cin >> N >> K;
    //cout << solve(N, K) << endl;
    cout << brute(N, K) << ' ' << solve(N, K) << '\n';
  }
}
