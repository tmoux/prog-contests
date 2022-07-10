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

const ll INV = -1;

struct Node { // {{{
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
}; // }}}

Node* seg;

const int maxn = 2e5+5, maxk = 19;
int N, Q;

vector<int> adj[maxn];

int tin[maxn], tout[maxn], t = 0;
int depth[maxn];
int par[maxk][maxn];

void dfs1(int i, int p) {
  tin[i] = t++;
  depth[i] = depth[p] + 1;
  par[0][i] = p;
  for (int k = 1; k < maxk; k++) {
    par[k][i] = par[k-1][par[k-1][i]];
  }
  for (int j: adj[i]) if (j != p) {
    dfs1(j, i);
  }
  tout[i] = t-1;
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) swap(a,b);
  for (int k = maxk - 1; k >= 0; k--) {
    int bb = par[k][b];
    if (bb != 0 && depth[bb] >= depth[a])
      b = bb;
  }
  if (a == b) return a;
  for (int k = maxk - 1; k >= 0; k--) {
    int aa = par[k][a];
    int bb = par[k][b];
    if (aa != bb) {
      a = aa;
      b = bb;
    }
  }
  return par[0][a];
}

int get_anc(int x) {
  return seg->getsum(tin[x], tin[x]);
}

bool query(vector<int> v) {
  int lc = v[0];
  for (int i = 1; i < sz(v); i++) {
    lc = lca(lc, v[i]);
  }
  seg->add(tin[lc], tout[lc], lc);
  set<int> s;

  sort(all(v), [&](int a, int b) {
    return depth[a] < depth[b];
  });
  for (auto x: v) {
    if (x == lc) continue;
    if (s.empty()) {
      s.insert(x);
    }
    else if (sz(s) == 1) {
      int y = *s.begin();
      int z = lca(x, y);
      if (z == y) {
        s.erase(y);
        s.insert(x);
      }
      else if (z == lc) {
        s.insert(x);
      }
      else return false;
    }
    else if (sz(s) == 2) {
      int y1 = *s.begin();
      int y2 = *next(s.begin());
      if (lca(x, y1) == y1) {
        s.erase(y1);
        s.insert(x);
      }
      else if (lca(x, y2) == y2) {
        s.erase(y2);
        s.insert(x);
      }
      else return false;
    }
    else assert(false);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  seg = new Node(0, N-1);
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs1(1, 0);
  /*
  FOR(i, 1, N+1) {
    cout << i << ' ' << depth[i] << endl;
  }
  cout << lca(1, 2) << endl;
  return 0;
  */

  cin >> Q;
  REP(Q) {
    int k; cin >> k;
    vector<int> v(k);
    for (auto& x: v) cin >> x;
    cout << (query(v) ? "YES" : "NO") << '\n';
  }
}
