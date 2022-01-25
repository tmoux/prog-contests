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

namespace Treap {
  mt19937 priority_rng(chrono::steady_clock::now().time_since_epoch().count());
  struct Treap {
    array<Treap*, 2> kids;
    std::uint_fast32_t priority;
    int subsize;

    int data;

    Treap(int);
  };

  int size(Treap* t) {
    return t ? t->subsize : 0;
  }

  void recalc(Treap* t) {
    if (!t) return;
    t->subsize = 1;
    for (auto c: t->kids) if (c) t->subsize += c->subsize;
  }

  Treap::Treap(int x) {
    kids = {nullptr, nullptr};
    priority = priority_rng();
    subsize = 1;
    data = x;
  }

  Treap* merge(Treap* l, Treap* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->priority < r->priority) {
      l->kids[1] = merge(l->kids[1], r);
      recalc(l);
      return l;
    }
    else {
      r->kids[0] = merge(l, r->kids[0]);
      recalc(r);
      return r;
    }
  }

  array<Treap*, 2> split(Treap* t, int k) { // left treap has k nodes
    if (!t) return {nullptr, nullptr};
    if (size(t->kids[0]) >= k) {
      auto [left, right] = split(t->kids[0], k);
      t->kids[0] = right;
      recalc(t);
      return {left, t};
    }
    else {
      k -= size(t->kids[0]) + 1;
      auto [left, right] = split(t->kids[1], k);
      t->kids[1] = left;
      recalc(t);
      return {t, right};
    }
  }

  void inorder(Treap* t) {
    if (!t) return;
    inorder(t->kids[0]);
    cout << t->data << ' ';
    inorder(t->kids[1]);
  }
} // namespace Treap

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  Treap::Treap* t = nullptr;
  for (int i = 1; i <= n; i++) {
    t = Treap::merge(t, new Treap::Treap(i));
  }

  // inorder(t);

  for (int i = 1; i <= n; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    if (b <= a) continue;
    // cout << "doing " << a << ' ' << b << endl;
    int l = min(b-a, n-b);
    if (l == b-a) {
      auto [t1, r4] = Treap::split(t, b+l);
      auto [t2, r3] = Treap::split(t1, b);
      auto [r1, r2] = Treap::split(t2, a);

      t = merge(r1, r3);
      t = merge(t, r2);
      t = merge(t, r4);
      
    }
    else {
      auto [t1, r4] = Treap::split(t, b);
      auto [t2, r3] = Treap::split(t1, a+l);
      auto [r1, r2] = Treap::split(t2, a);

      t = merge(r1, r4);
      t = merge(t, r3);
      t = merge(t, r2);

      assert(t);
    }
  }
  inorder(t);
  cout << '\n';

}
