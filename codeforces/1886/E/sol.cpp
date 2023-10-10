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

template<typename T>
void output_vector(const vector<T>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << (next(it) == v.end() ? '\n' : ' ');
  }
}

template<typename T>
void output_vector(const vector<T>& v, int offset) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << (*it + offset) << (next(it) == v.end() ? '\n' : ' ');
  }
}

const int maxn = 2e5+5, maxm = 20;
int N, M;
int A[maxn], B[maxm];

pair<int, int> dp[1 << maxm]; // min # needed to fulfill this mask, idx

int nxt[maxn][maxm]; // (i, j): if starting at i, what is min to satisfy j?
// nxt(i, j) = min with nxt(i+1, j)

template<typename T>
T ceil(T a, T b) {
  return (a + b - 1) / b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  vector<pair<int, int>> v;
  F0R(i, N) {
    cin >> A[i];
    v.emplace_back(A[i], i);
  }
  sort(A, A+N, greater());
  sort(all(v), greater());
  F0R(i, M) {
    cin >> B[i];
  }
  vector<int> toOrig(N);
  F0R(i, N) toOrig[i] = v[i].second;

  memset(nxt, -1, sizeof nxt);
  F0R(i, N) {
    F0R(j, M) {
      if (ceil(B[j], i+1) <= A[i]) {
        int x = ceil(B[j], A[i]);
        if (nxt[i-x+1][j] == -1) nxt[i-x+1][j] = i+1;
        else ckmin(nxt[i-x+1][j], i+1);
      }
    }
  }

  F0R(j, M) {
    for (int i = N-2; i >= 0; i--) {
      if (nxt[i][j] == -1) nxt[i][j] = nxt[i+1][j];
      else if (nxt[i+1][j] != -1) ckmin(nxt[i][j], nxt[i+1][j]);
    }
  }

  F0R(mask, 1 << M) dp[mask] = {-1, -1};
  dp[0] = {0, -1};
  F0R(mask, 1 << M) {
    if (dp[mask].first != -1) {
      int idx = dp[mask].first;
      F0R(i, M) {
        if (!(mask & (1 << i))) {
          int j = nxt[idx][i];
          if (j != -1) {
            int nmask = mask | (1 << i);
            if (dp[nmask].first == -1) dp[nmask] = {j, i};
            else ckmin(dp[nmask], {j, i});
          }
        }
      }
    }
  }

  int ALL = (1 << M) - 1;
  if (dp[ALL].first == -1) {
    cout << "NO\n";
  }
  else {
    int mask = ALL;
    vector<vector<int>> ans(M);
    while (mask) {
      int i = dp[mask].second;
      int nmask = mask ^ (1 << i);
      for (int j = dp[mask].first-1; j >= dp[nmask].first; j--)
        ans[i].push_back(toOrig[j]);
      mask = nmask;
    }

    cout << "YES\n";
    F0R(i, M) {
      cout << sz(ans[i]) << ' ';
      output_vector(ans[i], +1);
    }
  }
}
