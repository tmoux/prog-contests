#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

typedef long double ld;

struct FN
{
  ll m, b; //in this case, function is a line
  FN(ll _m, ll _b) : m(_m), b(_b) {}
  ll eval(ll x) const {
    return m*x + b;
  }

  ld intersect(const FN& r) const { //returns x coordinate of intersection
    //assert(m != r.m);
    return (ld)(r.b-b)/(ld)(m-r.m);
  }

  friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    //order in deque: l1, l2, l
    //true --> l2 is unnecessary
    ld x1 = l1.intersect(l);
    ld x2 = l1.intersect(l2);
    return x1 <= x2;
  }
};

struct Hull: public deque<FN> //convex hull for maximum
{
  void addFN(const FN& l) {
    while (size() >= 2 &&
           comp((*this)[size()-2],(*this)[size()-1],l)) {
      this->pop_back();
    }
    this->push_back(l);
  }

  ll query(ll x) {
    if (size() == 0) return -(1LL<<62); //handle empty hull
    while (size() >= 2 && (*this)[1].eval(x) >= (*this)[0].eval(x)) {
      pop_front();
    }
    return (*this)[0].eval(x);
  }
};

int dpl[3001][3001], dpr[3001][3001];

void solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  string s; cin >> s;
  F0R(i, N) A[i] = s[i] - '0';
  vector<ll> ans(N+1);

  auto F = [&]() -> void {
    F0R(i, N) F0R(c, K+1) dpl[i][c] = dpr[i][c] = 0;

    for (int i = 0; i < N; i++) {
      if (A[i] == 0) {
        for (int c = 0; c <= K; c++) {
          dpl[i][c] = (i == 0 ? 0 : dpl[i-1][c]) + 1;
        }
      }
      else {
        for (int c = 0; c < K; c++) {
          dpl[i][c+1] = (i == 0 ? 0 : dpl[i-1][c]) + 1;
        }
      }
    }
    for (int i = 1; i < N; i++) {
      for (int c = 0; c <= K; c++) {
        ckmax(dpl[i][c], dpl[i-1][c]);
        if (c > 0) ckmax(dpl[i][c], dpl[i][c-1]);
      }
    }

    for (int i = N-1; i >= 0; i--) {
      if (A[i] == 1) {
        for (int c = 0; c <= K; c++) {
          dpr[i][c] = (i == N-1 ? 0 : dpr[i+1][c]) + 1;
        }
      }
      else {
        for (int c = 0; c < K; c++) {
          dpr[i][c+1] = (i == N-1 ? 0 : dpr[i+1][c]) + 1;
        }
      }
    }
    for (int i = N-2; i >= 0; i--) {
      for (int c = 0; c <= K; c++) {
        ckmax(dpr[i][c], dpr[i+1][c]);
        if (c > 0) ckmax(dpr[i][c], dpr[i][c-1]);
      }
    }

    vector<int> mx(N+1, -1);

    for (int i = -1; i < N; i++) {
      for (int c = 0; c <= K; c++) {
        int m = i == -1 ? 0 : dpl[i][c];
        int b = i < N-1 ? dpr[i+1][K-c] : 0;
        ckmax(mx[m], b);
      }
    }

    for (int a = 1; a <= N; a++) {
      for (int k = 0; k <= N; k++) {
        if (mx[k] > -1) ckmax(ans[a], 1LL * a * k + mx[k]);
      }
    }
  };

  F(); reverse(all(A)); F();

  FOR(i, 1, N+1) {
    cout << ans[i] << " \n"[i == N];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
