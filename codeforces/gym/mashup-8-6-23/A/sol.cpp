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

const int maxn = 1005;
int N, M, K;

int cnt[26][maxn][maxn];
int sub[maxn][maxn];
ll orig[maxn][maxn]; // prefix sums
ll sums[26][maxn][maxn]; // prefix sums for each char

ll getsum(int x1, int y1, int x2, int y2, ll S[maxn][maxn]) {
  return S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1];
}

vector<ll> compute_distances(const vector<int>& C) {
  vector<ll> res(26);
  ll cur = 0;
  ll sum = 0;
  F0R(i, 26) {
    res[i] += cur;
    sum += C[i];
    cur += sum;
  }
  cur = 0, sum = 0;
  F0Rd(i, 26) {
    res[i] += cur;
    sum += C[i];
    cur += sum;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  vector<vector<int>> G(N+1, vector<int>(M+1));
  FOR(i, 1, N+1) {
    string s; cin >> s;
    FOR(j, 1, M+1) {
      G[i][j] = s[j-1] - 'a';
    }
  }
  vector<array<int, 5>> photos(K);
  F0R(i, K) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    char C; cin >> C;
    int e = C - 'a';
    photos[i] = {a, b, c, d, e};
    sub[a][b]++;
    sub[a][d+1]--;
    sub[c+1][b]--;
    sub[c+1][d+1]++;

    cnt[e][a][b]++;
    cnt[e][a][d+1]--;
    cnt[e][c+1][b]--;
    cnt[e][c+1][d+1]++;
  }


  F0R(c, 26) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        cnt[c][i][j] += cnt[c][i-1][j] + cnt[c][i][j-1] - cnt[c][i-1][j-1];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      sub[i][j] += sub[i-1][j] + sub[i][j-1] - sub[i-1][j-1];
      cnt[G[i][j]][i][j] += K - sub[i][j];
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      vector<int> C(26);
      F0R(c, 26) C[c] = cnt[c][i][j];
      auto dist = compute_distances(C);
      F0R(c, 26) {
        sums[c][i][j] += dist[c];
        sums[c][i][j] += sums[c][i-1][j] + sums[c][i][j-1] - sums[c][i-1][j-1];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      orig[i][j] = getsum(i, j, i, j, sums[G[i][j]]);
      orig[i][j] += orig[i-1][j] + orig[i][j-1] - orig[i-1][j-1];
    }
  }

  ll ans = 1e18;
  for (auto [a, b, c, d, e]: photos) {
    ll tr = getsum(1, 1, N, M, orig);
    tr -= getsum(a, b, c, d, orig);
    tr += getsum(a, b, c, d, sums[e]);

    ckmin(ans, tr);
  }
  cout << ans << '\n';
}
