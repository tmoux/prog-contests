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

struct Segtree {
  int N;
  vector<int> s, e;
  vector<int> val;

  static inline int lt(int x) { return x << 1; }
  static inline int rt(int x) { return (x << 1) | 1; }
  inline int isLeaf(int i) {
    return s[i] == e[i];
  }
  Segtree(int s_, int e_, const vector<int>& v) {
    N = e_ - s_ + 2;
    s.resize(4*N);
    e.resize(4*N);
    val.resize(4*N);

    init(1, s_, e_, v); 
  }

  void init(int i, int s_, int e_, const vector<int>& v) {
    s[i] = s_;
    e[i] = e_; 
    if (s[i] == e[i]) {
      val[i] = v[i];
    }
    else {
      int m_ = (s_+e_)/2;
      init(lt(i), s_, m_, v);
      init(rt(i), m_+1, e_, v);
      val[i] = val[lt(i)] + val[rt(i)];
    }
  }
};

struct Node {
  int s, e, m;
  //covers s,e;
  ll sum, trisum;
  Node *l, *r;

  ll merge(ll x, ll y, ll z, ll w) {
    return x + y + z * w;
  }

  Node(int a, int b) {
    s = a;
    e = b;
    sum = trisum = 0;
    if (s != e) {
      m = (s+e)/2;
      l = new Node(s,m);
      r = new Node(m+1,e);
    }
    else {
      l = nullptr;
      r = nullptr;
    }
  }

  void add(int i, int x) {
    if (s == e) {
      sum = trisum = x;
      return;
    }
    if (i <= m) {
      l->add(i,x);
    }
    else if (i > m) {
      r->add(i,x);
    }
    else assert(false);
    sum = l->sum + r->sum;
    trisum = merge(l->trisum, r->trisum, l->sum, r->e - r->s + 1);
  }

  ll getsum(int i) {
    if (s == e) return sum;
    if (i <= m) return l->getsum(i);
    else return merge(l->trisum, r->getsum(i), l->sum, i-m);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;

  Node *root = new Node(0, N);
  map<int, set<int>> indices;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    A[i] = x;
    int dist = indices[x].empty() ? i+1 : i - *indices[x].rbegin();
    root->add(i, dist);
    indices[x].insert(i);
  }

  auto update = [&](int i, int x) {
    auto it = indices[x].lower_bound(i);
    if (it != indices[x].begin()) {
      root->add(i, i-*prev(it));
    }
    else {
      root->add(i, i+1);
    }
  };

  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int i, y; cin >> i >> y;
      i--;
      int x = A[i];

      update(i, y);

      indices[x].erase(i);
      indices[y].insert(i);
      A[i] = y;

      auto it = indices[x].upper_bound(i);
      if (it != indices[x].end()) {
        update(*it, x);
      }

      it = indices[y].upper_bound(i);
      if (it != indices[y].end()) {
        update(*it, y);
      }
    }
    else if (t == 2) {
      int k; cin >> k; k--;
      ll ans = root->getsum(k);
      cout << ans << '\n';
    }
    else assert(false);
  }
}
