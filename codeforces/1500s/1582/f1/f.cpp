#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
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

  template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

const int maxn = 1e5+5, maxx = 505;
int dp[maxx][maxx<<1];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<pair<int,int>> a;
  F0R(i, n) {
    int ai; cin >> ai;
    a.push_back({ai, i});
  }
  sort(all(a));

  F0R(i, maxx) {
    F0R(j, maxx<<1) {
      dp[i][j] = maxn;
    }
  }
  dp[0][0] = -1;

  int pt = 0;
  for (int i = 0; i <= 500; i++) {
    while (pt < sz(a) && a[pt].first == i) {
      int idx = a[pt].second;
      if (i > 0) {
        F0R(j, maxx<<1) {
          if (idx > dp[i-1][j]) {
            ckmin(dp[i][j^i], idx);
          }
        }
      }
      pt++;
      /*
    if (i <= 12) {
      cout << i << ":\n";
      F0R(j, 17) {
        cout << j << ": " << dp[i][j] << '\n';
      }
    */
    }
    if (i > 0) F0R(j, maxx<<1) ckmin(dp[i][j], dp[i-1][j]);
  }

  vector<int> ans;
  F0R(j, maxx<<1) {
    //cout << j << ": " << dp[500][j] << '\n';
    if (dp[500][j] < maxn) ans.push_back(j);
  }

  //output
  cout << ans.size() << '\n';
  for (auto i: ans) {
    cout << i << ' ';
  }
  cout << '\n';
}
