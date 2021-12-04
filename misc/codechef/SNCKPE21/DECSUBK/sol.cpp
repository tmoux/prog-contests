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
// }}}

int longest_subsequence(vector<int> a) {
  vector<int> dp(a.size());
  for (int i = 0; i < sz(a); i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (a[j] <= a[i]) ckmax(dp[i], dp[j] + 1);
    }
  }
  return *max_element(all(dp));
}

void solve() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  map<int,int> cnt;
  for (auto& i: a) {
    cin >> i;
    cnt[i]++;
  }

  int mx = 0;
  for (auto [x, c]: cnt) ckmax(mx, c);
  if (k < mx) {
    cout << -1 << '\n';
    return;
  }
  sort(all(a));

  vector<int> b(n), dp(n);
  vector<bool> taken(n, false);
  for (int i = 0; i < n; i++) {
    bool found = false;
    for (int j = 0; j < n; j++) {
      if (!taken[j]) {
        vector<int> c = b;
        c[i] = a[j];

        int pt = i+1;
        for (int l = n-1; l >= 0; l--) {
          if (taken[l] || l == j) continue;
          c[pt++] = a[l];
        }

        // cout << "trying ";
        // for (auto i: c) cout << i << ' ';
        // cout << '\n';
        // cout << longest_subsequence(c) << endl;
        if (longest_subsequence(c) <= k) {
          found = true;
          taken[j] = true;
          b[i] = a[j];
          break;
        }
      }
    }
    assert(found);
  }

  for (auto i: b) {
    cout << i << ' ';
  }
  cout << endl;

  //cout << "k = " << k << endl;

  assert(longest_subsequence(b) == k);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
