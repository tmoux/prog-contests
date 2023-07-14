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

const ll INV = -1; //invalid number for lazy

struct Node {
  int s, e, m;
  //covers s,e;
  ll sum;
  ll lazy;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = INV;
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
    if (lazy == INV) return;
    if (s != e) {
      l->lazy = lazy;
      l->sum = (l->e - l->s + 1) * lazy;

      r->lazy = lazy;
      r->sum = (r->e - r->s + 1) * lazy;
    }
    lazy = INV;
  }

  void pull() {
    sum = l->sum + r->sum;
  }

  void add(int st, int en, ll x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy = x;
      sum = (e - s + 1) * x;
      return;
    }
    push();
    if (st <= m) {
      l->add(st,en,x);
    }
    if (en > m) {
      r->add(st,en,x);
    }
    pull();
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
};

bool solve() {
  int N, Q; cin >> N >> Q;
  string s, f; cin >> s >> f;
  vector<pair<int, int>> queries(Q);
  F0R(i, Q) {
    cin >> queries[i].first >> queries[i].second;
    queries[i].first--;
    queries[i].second--;
  }
  reverse(all(queries));

  Node seg(0, N-1);
  F0R(i, N) if (f[i] == '1') seg.add(i, i, 1);
  for (auto [l, r]: queries) {
    int len = r - l + 1;
    int oneCount = seg.getsum(l, r);
    int zeroCount = len - oneCount;
    if (oneCount * 2 < len) {
      // set all to 0
      seg.add(l, r, 0);
    }
    else if (zeroCount * 2 < len) {
      // set all to 1
      seg.add(l, r, 1);
    }
    else return false;
  }
  F0R(i, N) {
    if (seg.getsum(i, i) != (s[i] - '0')) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}
