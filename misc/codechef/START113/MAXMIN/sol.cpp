#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

/*
** BSTA (target >= T)
** Fix a split point for one at i
** Claim: it's optimal to take as many 1's as possible?
** Because 0's to the left are "better"
 */

int solve() {
  int N; cin >> N;
  string s; cin >> s;
  vector<int> A(N);
  vector<int> ones;
  vector<int> pfxZeros(N);
  F0R(i, N) {
    A[i] = s[i] - '0';
    if (A[i] == 1) ones.push_back(i);
    pfxZeros[i] = (A[i] == 0) + (i == 0 ? 0 : pfxZeros[i-1]);
  }

  vector<vector<int>> Lis(N+1, vector<int>(2));
  F0Rd(i, N) {
    Lis[i] = Lis[i+1];
    if (A[i] == 1) Lis[i][1]++;
    else {
      Lis[i][0]++;
      ckmax(Lis[i][0], Lis[i+1][1] + 1);
    }
  }
  auto lis = [&](int i) -> int {
    return max(Lis[i][0], Lis[i][1]);
  };

  auto check = [&](int T) -> bool {
    int Z = 0;
    int j = 0;
    for (int i = -1; i < N; i++) {
      if (i >= 0 && A[i] == 0) Z++;

      int x = min(T, sz(ones) - j);
      int z = T - x;
      if (z <= Z) {
        int k = j + x < sz(ones) ? ones[j + x] : N;
        // k is first index where we can use ones
        int cnt = ((k == 0 ? 0 : pfxZeros[k-1]) - z) + lis(k);
        if (cnt >= T) return true;
      }

      if (i >= 0 && A[i] == 1) j++;
    }
    return false;
  };

  int lo = 0, hi = N/2 + 1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    (check(mid) ? lo : hi) = mid;
  }
  return lo;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
