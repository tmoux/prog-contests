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

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  int pos = 0, neg = 0;
  vector<pair<int, int>> ans;
  auto ADD = [&](int i, int j) {
    A[i] += A[j];
    ans.push_back({i, j});
  };
  F0R(i, N) {
    cin >> A[i];
    if (A[i] < 0) neg++;
    else if (A[i] > 0) pos++;
  }
  if (pos > 0 && neg > 0) {
    pair<int, int> mn = {1e9, -1};
    pair<int, int> mx = {-1e9, -1};
    F0R(i, N) {
      ckmin(mn, {A[i], i});
      ckmax(mx, {A[i], i});
    }
    if (mx.first >= -mn.first) {
      if (neg <= 12) {
        F0R(i, N) {
          if (A[i] < 0) ADD(i, mx.second);
        }
      }
      else {
        while (-A[mn.second] < mx.first) {
          ADD(mn.second, mn.second);
        }
        F0R(i, N) {
          if (A[i] > 0) ADD(i, mn.second);
        }
      }
    }
    else {
      if (pos <= 12) {
        F0R(i, N) {
          if (A[i] > 0) ADD(i, mn.second);
        }
      }
      else {
        while (A[mx.second] < -mn.first) {
          ADD(mx.second, mx.second);
        }
        F0R(i, N) {
          if (A[i] < 0) ADD(i, mx.second);
        }
      }
    }
  }
  bool has_pos = 0;
  F0R(i, N) {
    if (A[i] > 0) {
      has_pos = 1;
      break;
    }
  }
  if (has_pos) {
    FOR(i, 1, N) {
      ADD(i, i-1);
    }
  }
  else {
    for (int i = N-2; i >= 0; i--) {
      ADD(i, i+1);
    }
  }
  assert(sz(ans) <= 31);
  cout << sz(ans) << '\n';
  for (auto [i, j]: ans) {
    cout << i+1 << ' ' << j+1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
