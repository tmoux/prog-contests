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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

struct PermGraph {
  const int MAGIC = 250;
  int n;
  vector<int> next, prev, jump;
  PermGraph(const vector<int>& p) {
    n = sz(p);
    next.resize(n);
    prev.resize(n);
    jump.resize(n);
    F0R(i, n) {
      next[i] = p[i];
      prev[p[i]] = i;
    }
    F0R(i, n) update(i);
  }

  void swap_vertices(int i, int j) { //i -> next[j], j -> next[i];
    prev[next[j]] = i;
    prev[next[i]] = j;
    swap(next[i], next[j]);
    update(i);
    update(j);
  }

  void update(int i) {
    int j = i;
    REP(MAGIC) {
      j = next[j];
    }
    jump[i] = j;
    REP(MAGIC) {
      i = prev[i];
      j = prev[j];
      jump[i] = j;
    }
  }

  int query(int i, int k) {
    while (k >= MAGIC) {
      i = jump[i];
      k -= MAGIC;
    }
    while (k > 0) {
      i = next[i];
      k--;
    }
    return i;
  }
};

 

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  vector<int> p(n);
  for (auto& i: p) {
    cin >> i; i--;
  }
  PermGraph perm_graph(p);
  while (q--) {
    //cout << perm_graph.next << '\n';
    //cout << perm_graph.prev << '\n';
    cout << perm_graph.jump << endl;
    int t; cin >> t;
    if (t == 1) {
      int x, y; cin >> x >> y;
      x--; y--;
      perm_graph.swap_vertices(x, y);
    }
    else if (t == 2) {
      int i, k; cin >> i >> k;
      i--;
      int ans = perm_graph.query(i, k);
      cout << ans+1 << '\n';
    }
    else assert(false);
  }
  pair<int, string> asdf = {3, "asdf"};
  cout << asdf << endl;
  vector<string> as = {"as", "bc", "sd"};
  cout << as << endl;
}
