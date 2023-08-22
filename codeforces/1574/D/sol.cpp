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
vector<int> A[10];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    int c; cin >> c;
    A[i].resize(c);
    F0R(j, c) cin >> A[i][j];
  }

  int M; cin >> M;
  set<vector<int>> banned;
  F0R(i, M) {
    vector<int> v;
    F0R(j, N) {
      int x; cin >> x;
      v.push_back(x);
    }
    banned.insert(v);
  }

  using T = pair<int, vector<int>>;
  vector<T> builds = {{0, {}}};
  F0R(i, N) {
    vector<T> nbuilds;
    if (1LL * sz(A[i]) * sz(builds) <= M+1) {
      F0R(j, sz(A[i])) {
        int x = A[i][j];
        for (auto [s, v]: builds) {
          v.push_back(j+1);
          nbuilds.emplace_back(s + x, v);
        }
      }
    }
    else {
      // Find least sum S such that # >= S is at least M+1
      int lo = 0, hi = 1e9+9;
      while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        ll cnt = 0;

        int idx = 0;
        F0R(j, sz(A[i])) {
          int x = A[i][j];
          while (idx < sz(builds) && builds[idx].first + x >= mid) idx++;
          cnt += idx;
        }

        (cnt >= M+1 ? lo : hi) = mid;
      }

      int S = lo;
      // cout << i << ": " << S << endl;
      int idx = 0;
      F0R(j, sz(A[i])) {
        int x = A[i][j];
        while (idx < sz(builds) && builds[idx].first + x >= S) idx++;
        for (int k = 0; k < idx; k++) {
          auto [s, v] = builds[k];
          v.push_back(j+1);
          nbuilds.emplace_back(s + x, v);
        }
      }
    }

    sort(all(nbuilds), greater<T>());
    builds = nbuilds;
    // cout << i << ": " << endl;
    // for (auto [s, v]: builds) {
    //   cout << s << ' ' << v << endl;
    // }
  }

  for (auto [s, v]: builds) {
    if (banned.count(v)) continue;
    else {
      for (auto x: v) {
        cout << x << ' ';
      }
      cout << '\n';
      return 0;
    }
  }
}
