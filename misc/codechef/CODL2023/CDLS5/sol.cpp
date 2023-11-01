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

std::optional<string> solve() {
  int N; cin >> N;
  string s; cin >> s;
  vector<int> freq(26, 0);
  for (char c: s) freq[c-'a']++;

  string ans;
  F0R(l, N) {
    char nxt = 'a'-1;
    F0R(i, 26) {
      if (!ans.empty() && ans.back()-'a' == i) continue;
      if (freq[i] > 0) {
        freq[i]--;
        pair<int, int> mx = {-1, -1};
        F0R(j, 26) ckmax(mx, {freq[j], j});
        int len = N - 1 - l;
        if (mx.first * 2 <= len ||
            (mx.first * 2 == len+1 && mx.second != i)) { // here mx.second is unique
          // found it
          nxt = i + 'a';
        }
        freq[i]++;
        if ('a' <= nxt && nxt <= 'z') break;
      }
    }
    if ('a' <= nxt && nxt <= 'z') {
      ans += nxt;
      freq[nxt-'a']--;
    }
    else return std::nullopt;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    auto o = solve();
    if (o) {
      cout << *o << '\n';
    }
    else {
      cout << -1 << '\n';
    }
  }
}
