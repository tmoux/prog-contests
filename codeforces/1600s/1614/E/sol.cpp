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

struct SegDyn
{
  int s, e, m; //represents range [s,e]
  SegDyn *l, *r;
  int sum; //sum for this interval
  SegDyn(int _s, int _e) {
    s = _s;
    e = _e;
    m = std::midpoint(s, e);
    l = NULL;
    r = NULL;
    sum = 0;
  }

  void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
  void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

  void pull() {
    sum = 0;
    if (l) sum += l->sum;
    if (r) sum += r->sum;
  }

  void add(int idx, int del) { //a[idx] += del
    //cout << s << ' ' << e << '\n';
    if (s == e && s == idx) {
      //at the node, stop
      sum += del;
      return;
    }
    if (idx <= m) {
      prepareL();
      assert(l);
      l->add(idx,del);
    }
    else {
      prepareR();
      r->add(idx,del);
    }
    pull(); //updates current node based on the children
  }

  int getsum(int se, int en) {
    if (se <= s && e <= en) return sum;
    int res = 0;
    if (l && se <= m) res += l->getsum(se,en);
    if (r && en > m) res += r->getsum(se,en);
    return res;
  }
};

int sum(SegDyn* node) {
  return node ? node->sum : 0;
}

int findMaxLt(SegDyn* node, int se, int en, int x) {
  if (se == en) {
    return se + sum(node) < x ? en : -1;
  }
  int m = std::midpoint(se, en);
  int lsum = node ? sum(node->l) : 0;
  SegDyn* nl = node ? node->l : nullptr;
  SegDyn* nr = node ? node->r : nullptr;
  if (m + lsum < x) {
    int i = findMaxLt(nr, m+1, en, x - lsum);
    return i != -1 ? i : m;
  }
  else return findMaxLt(nl, se, m, x);
}

int findMinGt(SegDyn* node, int se, int en, int x) {
  if (se == en) {
    return se + sum(node) > x ? en : -1;
  }
  int lsum = node ? sum(node->l) : 0;
  SegDyn* nl = node ? node->l : nullptr;
  SegDyn* nr = node ? node->r : nullptr;
  int m = std::midpoint(se, en);
  if (m + lsum > x) {
    return findMinGt(nl, se, m, x);
  }
  else return findMinGt(nr, m+1, en, x - lsum);
}


const int maxn = 2e5+5;
int N;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int MX = 2e9;
  SegDyn seg(0, MX);

  cin >> N;
  int last = 0;
  F0R(i, N) {
    int T; cin >> T;
    int j = findMaxLt(&seg, 0, MX, T);
    if (j >= 0 && j <= MX) {
      seg.add(0, 1);
      seg.add(j+1, -1);
    }

    j = findMinGt(&seg, 0, MX, T);
    if (j != -1 && j <= MX) {
      seg.add(j, -1);
    }

    int k; cin >> k;
    while (k--) {
      int x; cin >> x;
      const int MOD = 1e9+1;
      x = (x + last) % MOD;

      last = x + seg.getsum(0, x);
      cout << last << '\n';
    }
  }
}
