#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int N = 1e5 + 9;
const ll INF = 1e15;
int phi[N];
ll a[N], s1[N][320], s2[N][320];
int root[N];
void prep() {
  for (int i = 1; i < N; i++) phi[i] = i;
  for (int i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
  }
  for (int i = 1; i < N; i++) {
    a[i] = a[i - 1] + phi[i];
  }
  for (int i = 1; i < N; i++) {
    root[i] = 0;
    for (int j = 1; j * j <= i; j++) {
      s1[i][j] = s1[i][j - 1] + a[j] * (i / j - i / (j + 1));
      root[i] = j;
    }
    s2[i][i / (root[i] + 1) + 1] = s1[i][root[i]];
    for (int j = i / (root[i] + 1); j >= 1; j--) {
      s2[i][j] = s2[i][j + 1] + a[i / j];
    }
  }
}
ll C(int l, int r) {
  if (l > r) return INF;
  ll ans = 0;
  if (r / l <= root[r]) {
    return s1[r][r / l] - a[r / l] * (l - 1 - r / ((r / l) + 1));
  }
  else {
    return s2[r][l];
  }
  return ans;
}

const int MK = 18;
vector<ll> dp_before, dp_cur;

void compute(int l, int r, int optl, int optr) {
  if (l > r) return;
  int mid = std::midpoint(l, r);
  pair<ll, int> best = {INF, -1};

  for (int j = optl; j <= min(mid, optr); j++) {
    ckmin(best, {dp_before[j] + C(j+1, mid), j});
  }

  dp_cur[mid] = best.first;
  int opt = best.second;

  compute(l, mid-1, optl, opt);
  compute(mid+1, r, opt, optr);
}

ll dp[MK][N];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  prep();
  dp_before.resize(N, INF);
  dp_before[0] = 0;
  dp_cur.resize(N);
  for (int k = 1; k < MK; k++) {
    compute(1, N-1, 0, N-1);
    FOR(n, 1, N) dp[k][n] = dp_cur[n];
    dp_before = dp_cur;
  }

  int T; cin >> T;
  while (T--) {
    int n, k; cin >> n >> k;
    cout << (k < MK ? dp[k][n] : n) << '\n';
  }
}
