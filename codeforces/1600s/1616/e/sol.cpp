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

template<typename T>
T maxv(T a) { return a; }
template<typename T, typename ... Args>
T maxv(T a, Args ... args) { return std::max(a, maxv(args...)); }

template<typename T>
T minv(T a) { return a; }
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
// }}}

struct Fenwick
{
    int n;
    vector<int> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, int x) {
        i++;
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    int sum(int i) const {
        i++;
        int r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

const ll INF = 1e18;
struct IndexTracker {
  vector<int> indices[26];
  Fenwick fen;

  IndexTracker(const string& s) : fen(sz(s)) {
    int n = sz(s);
    F0R(i, 26) indices[i].clear();
    for (int i = n-1; i >= 0; i--) {
      indices[s[i]-'a'].push_back(i);
    }
  }

  bool canAddChar(char c) const {
    return !indices[c-'a'].empty();
  }

  ll addChar(char c, int i) {
    assert(!indices[c-'a'].empty());
    int idx = indices[c-'a'].back();

    indices[c-'a'].pop_back();
    fen.add(0, 1);
    fen.add(idx, -1);

    int ans = idx + fen.sum(idx) - i;
    return ans;
  }

  ll minIndex(char c) const {
    if (indices[c-'a'].empty()) return INF;
    else {
      int idx = indices[c-'a'].back();
      return idx + fen.sum(idx);
    }
  }
};

ll solve() {
  int n; cin >> n;
  string s, t; cin >> s >> t;
  string sorted_s = s; sort(all(sorted_s));
  if (s < t) {
    return 0;
  }
  else if (sorted_s < t) { //possible
    IndexTracker tracker(s);
    ll ans = INF;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
      for (char c = 'a'; c < t[i]; c++) {
        ckmin(ans, cur + tracker.minIndex(c) - i);
      }
      if (tracker.canAddChar(t[i])) {
        cur += tracker.addChar(t[i], i);
      }
      else break;
    }
    assert(ans < INF);
    return ans;
  }
  else return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}
