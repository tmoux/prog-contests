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

int N, M;
vector<vector<int>> A;

vector<int> hamming(int i, int j) {
  vector<int> v;
  F0R(k, M) {
    if (A[i][k] != A[j][k]) v.push_back(k);
  }
  return v;
}

void imposs() {
  cout << "No\n";
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  A.resize(N+1, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) cin >> A[i][j];
  }
  F0R(j, M) A[N][j] = A[0][j];

  pair<int, pair<int, vector<int>>> maxDiff = {0, {0, {}}};
  FOR(i, 1, N) {
    auto v = hamming(0, i);
    int d = sz(v);
    if (d > 4) imposs();
    ckmax(maxDiff, {d, {i, v}});
  }

  if (maxDiff.first <= 2) {
    cout << "Yes\n";
    F0R(j, M) {
      cout << A[0][j] << ' ';
    }
    cout << '\n';
    return 0;
  }
  else {
    auto v = maxDiff.second.second;
    int idx = maxDiff.second.first;
    // cout << v << endl;
    // cout << idx << endl;
    F0R(mask, 1 << sz(v)) {
      vector<int> change;
      F0R(i, sz(v)) {
        if (mask & (1 << i)) change.push_back(v[i]);
      }
      if (sz(change) <= 2 && sz(v)-sz(change) <= 2) {
        for (auto j: change) A[N][j] = A[idx][j];

        // cout << "checking " << A[N] << endl;
        int maxd = 0;
        F0R(i, N) {
          ckmax(maxd, sz(hamming(N, i)));
        }
        if (maxd <= 2) {
          cout << "Yes\n";
          F0R(j, M) {
            cout << A[N][j] << ' ';
          }
          cout << '\n';
          return 0;
        }

        for (auto j: change) A[N][j] = A[0][j];
      }
    }

    imposs();
  }
}
