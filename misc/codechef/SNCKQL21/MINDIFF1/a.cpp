#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

/* Waiting for c++20 on cf...
template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};
*/

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) //requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int maxn = 3e5+5;

void solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  vector<int> deg(N);
  F0R(_, M) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }
  set<pair<int,int>> s;
  F0R(i, N) s.insert({deg[i], i});
  vector<int> ans(N);
  FORd(c, 1, N+1) {
    assert(!s.empty());
    auto [d, i] = *s.begin();
    s.erase(s.begin());
    ans[i] = c;
    //cout << i << ' ' << c << endl;

    for (int j: adj[i]) {
      if (s.count({deg[j], j})) {
        s.erase({deg[j], j});
        deg[j]--;
        s.insert({deg[j], j});
      }
    }
  }

  vector<int> d(N);
  F0R(i, N) {
    for (int j: adj[i]) {
      if (ans[j] < ans[i]) d[i]++;
    }
  }
  int maxdi = *max_element(all(d));
  int mindi = *min_element(all(d));
  cout << maxdi-mindi << '\n';
  F0R(i, N) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
