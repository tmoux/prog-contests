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

struct Node {
  int s, e, m;
  ll sum;
  ll lazy;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = 0;
    if (s != e) {
      m = (s+e)/2;
      l = new Node(s,m);
      r = new Node(m+1,e);
    }
    else {
      l = NULL;
      r = NULL;
    }
  }

  void push() {
    if (s != e) {
      l->lazy += lazy;
      l->sum += (l->e - l->s + 1) * lazy;

      r->lazy += lazy;
      r->sum += (r->e - r->s + 1) * lazy;
    }
    lazy = 0;
  }

  void add(int st, int en, ll x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy += x;
      sum += (e - s + 1) * x;
      return;
    }
    push();
    if (st <= m) {
      l->add(st,en,x);
    }
    if (en > m) {
      r->add(st,en,x);
    }
    sum = l->sum + r->sum;
  }

  ll getsum(int st, int en) {
    push();
    //if completely included
    if (st <= s && e <= en) {
      return sum;
    }
    ll ret = 0;
    if (st <= m) {
      ret += l->getsum(st,en);
    }
    if (en > m) {
      ret += r->getsum(st,en);
    }
    return ret;
  }

  int min_index(int K) {
    if (s == e) {
      return s;
    }
    push();
    if (l->sum < K) {
      return r->min_index(K - l->sum);
    }
    else return l->min_index(K);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vector<int> L(N);
  F0R(i, N) {
    cin >> L[i];
  }
  sort(all(L), greater());

  const int MX = 2e5+1;
  Node seg(0, MX);
  seg.add(0, 0, 1);
  int ans = 1e9;
  int i = 0;
  for (auto l: L) {
    while (i < MX && seg.getsum(i, i) == 0) {
      i++;
    }
    if (i+2 <= MX) {
      seg.add(i, i, -1);
      int len = (l - 1) / 2;
      if (i+2 < MX) seg.add(i+2, min(MX-1, i+2+len-1), 2);
      if (l-1-2*len > 0 && i+2+len < MX) seg.add(i+2+len, i+2+len, 1);
    }
    if (seg.getsum(0, MX) >= K) {
      int index = seg.min_index(K);
      ckmin(ans, index);
    }
  }

  cout << (ans < 1e9 ? ans : -1) << '\n';
}
