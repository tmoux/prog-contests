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
  int T; cin >> T;
  while (T--) {
    int n, k; cin >> n >> k;
    if (k == n || k == n-2) {
      cout << -1 << '\n';
    }
    else {
      vector<pair<int,int>> edges;
      if (k > 0) {
        for (int i = 1; i <= k; i++) {
          edges.push_back({i, k+1});
        }
        for (int i = k+2; i <= n; i++) {
          edges.push_back({k+1, i});
          if ((i-(k+2)) % 2 == 0) {
            if (i < n) edges.push_back({i, i+1});
            else edges.push_back({i, i-1});
          }
        }
      }
      else {
        if (n <= 5) {
          for (int i = 1; i <= n-1; i++) {
            edges.push_back({i, i+1});
          }
          edges.push_back({1, n});
        }
        else if (n == 6) {
          edges.push_back({1, 2});
          edges.push_back({1, 3});
          edges.push_back({1, 4});
          edges.push_back({2, 5});
          edges.push_back({3, 6});
          edges.push_back({4, 6});
          edges.push_back({5, 6});
        }
        else {
          for (int i = 1; i <= k; i++) {
            edges.push_back({i, k+1});
          }
          for (int i = k+2; i <= n; i++) {
            edges.push_back({k+1, i});
            if ((i-(k+2)) % 2 == 0) {
              if (i < n) edges.push_back({i, i+1});
              else edges.push_back({i, i-1});
            }
          }
        }
      }
      cout << sz(edges) << '\n';
      for (auto [u, v]: edges) {
        cout << u << ' ' << v << '\n';
      }
    }
  }
}
