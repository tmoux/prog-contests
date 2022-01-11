#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

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

struct Fenwick
{
  int n;
  vector<int> bit;
  Fenwick() {}
  Fenwick(int n_) {
    n = n_;
    bit.resize(n+1,0);
  }
  void add(int i, int x) {
    i++;
    for (; i <= n; i += i & (-i))
      bit[i] += x;
  }

  int sum(int i) {
    i++;
    int r = 0;
    for (; i; i -= i & (-i)) {
      r += bit[i];
    }
    return r;
  }
};

struct IndexTracker {
  vector<vector<int>> indices;
  Fenwick fen;

  IndexTracker(string s) {
    indices.resize(26);
    for (int i = sz(s)-1; i >= 0; i--) {
      indices[s[i]-'a'].push_back(i);
    }
    fen = Fenwick(sz(s));
  }

  int moveChar(char c, int j) {
    int i = indices[c-'a'].back();
    indices[c-'a'].pop_back();
    fen.add(0, 1);
    fen.add(i, -1);
    return i + fen.sum(i) - j;
  }
};

ll subtask3(int n, string sa, string sb) {
  IndexTracker it(sb);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += it.moveChar(sa[i], i);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  string s; cin >> s;

  map<char, int> total, cnt;
  for (char c: s) total[c]++;
  
  IndexTracker it(s);
  ll ans = 0;
  string sa, sb;
  for (int i = 0, j = 0; i < 2*n; i++) {
    if (++cnt[s[i]] <= total[s[i]]/2) {
      ans += it.moveChar(s[i], j++);
      sa += s[i];
    }
    else sb += s[i];
  }

  // cout << ans << endl;
  // cout << sa << '\n';

  ans += subtask3(n, sa, sb);
  cout << ans << '\n';
}
