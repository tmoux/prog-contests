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
  int N, D; cin >> N >> D;
  vector<int> B(N), C(N);
  F0R(i, N) cin >> B[i];
  F0R(i, N) cin >> C[i];
  if (B[0] != C[0]) {
    cout << "NO\n";
    return;
  }
  else {
    vector<int> v = {0};
    for (int i = 1; i < N; i++) {
      if (B[i] > B[i-1] && C[i] < C[i-1]) {
        cout << "NO\n";
        return;
      }
      else if (B[i] > B[i-1] || C[i] < C[i-1]) {
        v.push_back(i);
      }
    }
    vector<int> A(N);
    int prev = 0;
    for (int i: v) {
      if (i == 0) {
        A[i] = B[0];
      }
      else if (B[i] > B[i-1]) {
        if (B[i] - A[prev] > 1LL * (i - prev) * D) {
          cout << "NO\n";
          return;
        }
        else {
          A[i] = B[i];
          for (int j = i-1; j > prev; j--) {
            A[j] = max(A[prev], A[j+1] - D);
          }
        }
      }
      else if (C[i] < C[i-1]) {
        if (A[prev] - C[i] > 1LL * (i - prev) * D) {
          cout << "NO\n";
          return;
        }
        else {
          A[i] = C[i];
          for (int j = i-1; j > prev; j--) {
            A[j] = min(A[prev], A[j+1] + D);
          }
        }
      }
      else assert(false);

      prev = i;
    }
    for (int i = v.back()+1; i < N; i++) {
      A[i] = A[v.back()];
    }
    // FOR(i, 1, N) {
    //   assert(abs(A[i] - A[i-1]) <= D);
    // }
    vector<int> minA = A, maxA = A;
    FOR(i, 1, N) {
      ckmin(minA[i], minA[i-1]);
      ckmax(maxA[i], maxA[i-1]);
    }
    if (maxA == B && minA == C) {
      cout << "YES\n";
      output_vector(A);
    }
    else {
      cout << "NO\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
