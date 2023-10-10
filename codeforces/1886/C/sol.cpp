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

char solve() {
  string s; cin >> s;
  int N = sz(s);
  ll pos; cin >> pos; pos--;

  auto getmin = [&](string s) {
    string ret = s.substr(1);
    for (int i = 1; i < sz(s); i++) {
      string t = s.substr(0, i) + s.substr(i+1);
      ckmin(ret, t);
    }
    return ret;
  };

  // string S, cur = s;
  // while (!cur.empty()) {
  //   S += cur;
  //   cur = getmin(cur);
  // }
  // DEBUG(S);

  vector<pair<char, int>> st = {{s[0], 0}};
  vector<pair<char, int>> v;
  for (int i = 1; i < N; i++) {
    auto [a, idx] = st.back();
    char b = s[i];
    if (a > b) {
      v.emplace_back(a, idx);
      st.pop_back();
      st.emplace_back(b, i);
    }
    else {
      st.emplace_back(b, i);
    }

    while (sz(st) >= 2 && st[sz(st)-2].first > st.back().first) {
      auto x = st.back(); st.pop_back();
      auto y = st.back(); st.pop_back();
      st.push_back(x);
      v.push_back(y);
    }
  }
  // DEBUG(v);
  // cout << st << endl;
  while (!st.empty()) {
    v.push_back(st.back());
    st.pop_back();
  }

  // string T;
  // for (int iter = 0; iter < sz(v); iter++) {
  //   vector<pair<int, char>> vec;
  //   for (int i = iter; i < sz(v); i++) {
  //     vec.emplace_back(v[i].second, v[i].first);
  //   }
  //   sort(all(vec));
  //   for (auto [_, c]: vec) T += c;
  // }
  // DEBUG(T);
  // assert(S == T);

  // cout << v << endl;
  int iter = 0;
  for (int len = N; pos - len >= 0; len--) {
    pos -= len;
    iter++;
  }
  vector<pair<int, char>> t;
  for (int i = iter; i < sz(v); i++) {
    t.emplace_back(v[i].second, v[i].first);
  }
  sort(all(t));
  return t[pos].second;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve();
  cout << '\n';
}
