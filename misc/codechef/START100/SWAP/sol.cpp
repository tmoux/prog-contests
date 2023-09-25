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
  int K; cin >> K;
  string s; cin >> s;
  string t = s; sort(all(t));
  vector<pair<int, int>> ans;
  auto op = [&](int l, int r) -> void {
    assert(l > 0 && r > 0);
    ans.emplace_back(l, r);
    string a = s.substr(0, l);
    string b = s.substr(l, N-l-r);
    string c = s.substr(l+(N-l-r), r);
    s = c + b + a;
  };

  // move middle char to left end
  {
    char c = t[N/2];
    int idx = -1;
    for (int j = 0; j < N; j++) {
      if (s[j] == c) {
        idx = j;
        break;
      }
    }
    if (idx != 0) {
      op(idx, N-idx);
    }
  }
  int l = N/2-1, r = N/2+1;
  int len = 1;
  int which = 0;
  while (s != t) {
    // cout << s << ' ' << l << ' ' << r << endl;
    if (which == 0) {
      // add from left
      int idx = -1;
      char c = t[l];
      for (int j = len; j < N; j++) {
        if (s[j] == c) {
          idx = j;
          break;
        }
      }
      // DEBUG(idx);
      assert(idx != -1);
      if (idx == N-1) {
        op(len, N-len);
      }
      else {
        op(len, N-1-idx);
      }
      len++;
      l--;
    }
    else {
      int idx = -1;
      char c = t[r];
      for (int j = N-1-len; j >= 0; j--) {
        if (s[j] == c) {
          idx = j;
          break;
        }
      }
      assert(idx != -1);
      if (idx == 0) {
        op(N-len, len);
      }
      else {
        op(idx, len);
      }
      len++;
      r++;
    }
    which ^= 1;
  }

  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << a << ' ' << b << '\n';
  }
  assert(s == t);
  assert(sz(ans) <= N);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
