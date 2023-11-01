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
  int Q; cin >> Q;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  vector<int> X(Q);
  F0R(i, Q) cin >> X[i];

  vector<int> Cur(N);
  F0R(i, N) {
    while (A[i] % (1 << (Cur[i]+1)) == 0) Cur[i]++;
  }
  vector<vector<int>> nxt(Q+1, vector<int>(31, Q));
  for (int i = Q-1; i >= 0; i--) {
    int x = X[i];
    for (int j = 1; j <= 30; j++) {
      if (j >= x) {
        nxt[i][j] = i;
      }
      else {
        ckmin(nxt[i][j], nxt[i+1][j]);
      }
      ckmin(nxt[i][j], nxt[i][j-1]);
    }
  }

  vector<int> B(N);
  F0R(i, N) {
    int cur = 0;
    while (A[i] % (1 << (cur+1)) == 0) cur++;
    int ans = A[i];
    int j = 0;
    // DEBUG(i);
    // DEBUG(cur);
    while (j < Q) {
      int nj = nxt[j][cur];
      if (nj >= Q) break;
      // cout << "index " << nj << ' ' << X[nj] << endl;
      ans |= 1 << (X[nj] - 1);
      cur = X[nj] - 1;
      j = nj + 1;
    }
    B[i] = ans;
  }
  output_vector(B);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
