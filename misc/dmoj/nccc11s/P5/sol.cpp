#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int N, Q, A, B;

int a = A, b = B, C = ~(1<<31), M = (1<<16)-1;
int rnd(int last) {
  a = (36969 + (last >> 3)) * (a & M) + (a >> 16);
  b = (18000 + (last >> 3)) * (b & M) + (b >> 16);
  return (C & ((a << 16) + b)) % 1000000000;
}

const int maxn = 1e5+5;
int AA[maxn], BB[maxn];

// persistent segtree {{{
const int MV = 2000000;
int l[MV], r[MV];
int sum[MV];
int nv = 0;
int rp[maxn];
const int SZ = maxn;

int build(int tl, int tr) {
  if (tl == tr) return nv++;
  int tm = (tl + tr) / 2;
  int cv = nv;
  nv++;
  l[cv] = build(tl, tm);
  r[cv] = build(tm+1, tr);
  sum[cv] = sum[l[cv]] + sum[r[cv]];
  return cv;
}

int query(int v, int tl, int tr, int L, int R) {
  if (L > R) return 0;
  if (L == tl && R == tr) return sum[v];
  int tm = (tl+tr)/2;
  return query(l[v], tl, tm, L, min(R, tm)) + query(r[v], tm+1, tr, max(L, tm+1), R);
}

int update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    sum[nv] = new_val + sum[v];
    return nv++;
  }
  int tm = (tl+tr)/2;
  if (pos <= tm) {
    int cv = nv; nv++;
    l[cv] = update(l[v], tl, tm, pos, new_val);
    r[cv] = r[v];
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  } else {
    int cv = nv; nv++;
    l[cv] = l[v];
    r[cv] = update(r[v], tm+1, tr, pos, new_val);
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  }
}
// }}}

int count_less(int x, int l, int r) {
  return query(rp[r], 1, N, )
}

struct Node {
  int s, e, m;
  //covers s,e;
  int sum;
  int lazy;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = -1;
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
    if (s != e && lazy != -1) {
      l->lazy = lazy;
      l->sum = count_less(lazy, l->s, l->e);

      r->lazy = lazy;
      r->sum = count_less(lazy, r->s, r->e);
    }
    lazy = -1;
  }

  void add(int st, int en, int x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy = x;
      sum = count_less(lazy, e, s);
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

  int getsum(int st, int en) {
    push();
    //if completely included
    if (st <= s && e <= en) {
      return sum;
    }
    int ret = 0;
    if (st <= m) {
      ret += l->getsum(st,en);
    }
    if (en > m) {
      ret += r->getsum(st,en);
    }
    return ret;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q >> A >> B;
  for (int i = 1; i <= N; i++) {
    cin >> AA[i];
  }
  for (int i = 1; i <= N; i++) {
    cin >> BB[i];
  }

  Node *seg = new Node(1, N);
  for (int i = 1; i <= N; i++) {
    seg->add(i, i, AA[i]);
  }

  int last = 0;
  int ans = 0;
  FOR(q, 1, Q+1) {
    int l = rnd(last) % N + 1;
    int r = rnd(last) % N + 1;
    int x = rnd(last) % N + 1;

    if (l > r) swap(l, r);
    if ((l + r + x) % 2 == 0) {
      // query
    }
    else {
      // update

      int res = 0;
      ans = (ans + 1LL * q * res) % 998244353;
    }
  }
  cout << ans << '\n';
}
