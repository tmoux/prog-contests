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

void solve() {
  int N; cin >> N;
  int X; cin >> X;
  if ((N & 1) && X == (N + 1) / 2) {
    cout << -1 << '\n';
    return;
  }
  if (N&1) {
    int m = (N + 1) / 2;
    auto flip = [&](int x) {
      return N + 1 - x;
    };
    vector<int> ans(N);
    ans[N/2] = m;
    ans[0] = X, ans[N-1] = flip(X);
    int j = 1;
    FOR(i, 1, m) {
      if (i == X || i == flip(X)) continue;
      ans[j] = i;
      ans[N-1-j] = flip(i);
      j++;
    }
    output_vector(ans);
  }
  else {
    int m = N / 2;
    auto flip = [&](int x) {
      return N + 1 - x;
    };
    vector<int> ans(N);
    ans[0] = X, ans[N-1] = flip(X);
    int j = 1;
    FOR(i, 1, N/2+1) {
      if (i == X || i == flip(X)) continue;
      ans[j] = i;
      ans[N-1-j] = flip(i);
      j++;
    }
    output_vector(ans);
  }
  // vector<int> P(N); iota(all(P), 1);
  // do {
  //   vector<int> d;
  //   FOR(i, 1, N) {
  //     d.push_back(P[i] - P[i-1]);
  //   }
  //   vector<int> dr = d; reverse(all(dr));
  //   if (d == dr) {
  //     cout << P << endl;
  //   }
  // } while (next_permutation(all(P)));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
