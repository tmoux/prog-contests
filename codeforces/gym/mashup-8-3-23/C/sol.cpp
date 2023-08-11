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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  ll K; cin >> K;
  K -= N;

  auto getL = [&](int n) {
    return 1LL * n * (n - 1) / 2;
  };
  auto getR = [&](int n) {
    return getL(n) + 1LL * n * n / 4;
  };
  ll L = getL(N);
  ll R = getR(N);
  if (K < L) {
    cout << -1 << '\n';
  }
  else if (K >= R) {
    cout << R + N << '\n';
    F0R(i, N) {
      cout << i+1 << ' ';
    }
    cout << '\n';
    F0Rd(i, N) {
      cout << i+1 << ' ';
    }
    cout << '\n';
  }
  else {
    cout << L << ' ' << R << ": " << K << endl;
    cout << K + N << '\n';
    vector<vector<ll>> A(2, vector<ll>(N, -1));
    int i = 0;
    for (int n = N; n >= 1; n--) {
      cout << n << ": " << K << endl;
      // assert(getL(n) <= K && K <= getR(n));
      if (getL(n-1) <= K - (n-1) && getR(n-1)) {
        A[0][i] = A[1][i] = n-1;
        i++;
        K -= (n-1);
      }
      else if (getL(n-1) <= K - 2*(n-1) && getR(n-1)) {
        A[0][i++] = n-1;
        A[1][i++] = n-1;
        K -= 2*(n-1);
      }
      else {

      }
    }


    F0R(i, N) {
      cout << A[0][i]+1 << ' ';
    }
    cout << '\n';
    F0R(i, N) {
      cout << A[1][i]+1 << ' ';
    }
    cout << '\n';
    ll check = 0;
    F0R(i, N) {
      check += max(A[0][i], A[1][i]);
    }
    DEBUG(check + N);
  }

  return 0;

  vector<int> p(N);
  iota(all(p), 0);
  int mn = 2e9, mx = -2e9;
  set<int> S;
  do {
    vector<int> q(N);
    iota(all(q), 0);
    do {
      int r = 0;
      F0R(i, N) r += max(p[i], q[i]);
      ckmin(mn, r);
      ckmax(mx, r);
      // S.insert(r);
    } while (next_permutation(all(q)));
  } while (next_permutation(all(p)));
  cout << mn << ' ' << mx << '\n';
}
