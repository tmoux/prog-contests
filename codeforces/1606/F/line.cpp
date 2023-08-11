// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

// https://codeforces.com/blog/entry/86731
const int inf = 2e9;
template<typename data_t>
struct Line {
  data_t a, b;
  Line() : a(0), b(inf) {}
  Line(data_t a, data_t b) : a(a), b(b) {}
  data_t get(data_t x) {
    return a * x + b;
  }
  void add(Line x) {
    a += x.a;
    b += x.b;
  }

  friend ostream &operator<<(ostream &os, const Line &p) {
    return os << p.a << "x + " << p.b;
  }
};

class LiChao {
  private:
    using data_t = double;

    struct Node {
      Line<data_t> line = Line<data_t>();
      Line<data_t> lazy = Line<data_t>(0, 0);

      Node *lc = nullptr;
      Node *rc = nullptr;

      void apply(int l, int r, Line<data_t> v) {
        line.add(v);
        lazy.add(v);
      }
    };

    int SZ;
    Node *root = nullptr;

    void PushLazy(Node* &n, int tl, int tr) {
      if (n == nullptr) return;
      if (n->lc == nullptr) n->lc = new Node();
      if (n->rc == nullptr) n->rc = new Node();
      int mid = (tl + tr) / 2;
      n->lc->apply(tl, mid, n->lazy);
      n->rc->apply(mid + 1, tr, n->lazy);
      n->lazy = Line<data_t>(0, 0);
    }

    void PushLine(Node* &n, int tl, int tr) {
      if (n == nullptr) return;
      int mid = (tl + tr) / 2;
      InsertLineKnowingly(n->lc, tl, mid, n->line);
      InsertLineKnowingly(n->rc, mid + 1, tr, n->line);
      n->line = Line<data_t>();
    }

    void InsertLineKnowingly(Node* &n, int tl, int tr, Line<data_t> x) {
      if (n == nullptr) n = new Node();
      if (n->line.get(tl) > x.get(tl)) swap(n->line, x);
      if (n->line.get(tr) <= x.get(tr)) return;
      if (tl == tr) return;
      int mid = (tl + tr) / 2;
      PushLazy(n, tl, tr);
      if (n->line.get(mid) <= x.get(mid)) {
        InsertLineKnowingly(n->rc, mid + 1, tr, x);
      } else {
        swap(n->line, x);
        InsertLineKnowingly(n->lc, tl, mid, x);
      }
    }

    void InsertLine(Node* &n, int tl, int tr, int l, int r, Line<data_t> x) {
      if (tr < l || r < tl || tl > tr || l > r) return;
      if (n == nullptr) n = new Node();
      if (l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
      int mid = (tl + tr) / 2;
      PushLazy(n, tl, tr);
      InsertLine(n->lc, tl, mid, l, r, x);
      InsertLine(n->rc, mid + 1, tr, l, r, x);
    }

    void AddLine(Node* &n, int tl, int tr, int l, int r, Line<data_t> x) {
      if (tr < l || r < tl || tl > tr || l > r) return;
      if (n == nullptr) n = new Node();
      if (l <= tl && tr <= r) return n->apply(tl, tr, x);
      int mid = (tl + tr) / 2;
      PushLazy(n, tl, tr);
      PushLine(n, tl, tr);
      AddLine(n->lc, tl, mid, l, r, x);
      AddLine(n->rc, mid + 1, tr, l, r, x);
    }

    data_t Query(Node* &n, int tl, int tr, int x) {
      if (n == nullptr) return inf;
      if (tl == tr) return n->line.get(x);
      data_t res = n->line.get(x);
      int mid = (tl + tr) / 2;
      PushLazy(n, tl, tr);
      if (x <= mid) {
        res = min(res, Query(n->lc, tl, mid, x));
      } else {
        res = min(res, Query(n->rc, mid + 1, tr, x));
      }
      return res;
    }

  public:
    set<int> pts;
    LiChao() {}
    LiChao(int _SZ) : SZ(_SZ) {
      pts.insert(0);
      pts.insert(SZ-1);
    }

    void InsertLine(int l, int r, Line<data_t> x) {
      InsertLine(root, 0, SZ - 1, l, r, x);
    }
    void AddLine(int l, int r, Line<data_t> x) {
      pts.insert(l);
      pts.insert(r+1);
      return AddLine(root, 0, SZ - 1, l, r, x);
    }
    int Query(int x) {
      return min(inf, (int)Query(root, 0, SZ - 1, x));
    }

    friend void merge(LiChao& a, LiChao& b, int i, int j) {
      if (sz(a.pts) < sz(b.pts)) swap(a, b);
      for (auto it = b.pts.begin(); next(it) != b.pts.end(); ++it) {
        int L = *it, R = *next(it);
        int y1 = b.Query(L), y2 = b.Query(R);
        data_t m = (y2 - y1) / (R - L);
        data_t b = y1 - m * L;
        a.AddLine(L, R-1, {m, b});
        // cout << i << ' ' << j << ": ";
        // cout << "adding line " << Line(m, b) << " on " << L << ' ' << R-1 << endl;
      }
      // cout << "NODE " << i << ": ";
      // F0R(k, 10) {
      //   cout << a.Query(k) << ' ';
      // }
      // cout << endl;

      b.pts.clear();
    }
};

const int maxn = 2e5+5;
int N;

vector<int> adj[maxn];
vector<pair<int, int>> queries[maxn];
int ans[maxn];

LiChao* DFS(int i, int p) {
  LiChao* L = new LiChao(maxn);
  L->InsertLine(0, maxn-1, {0, 0});
  for (int j: adj[i]) {
    if (j == p) continue;
    LiChao* M = DFS(j, i);
    merge(*L, *M, i, j);
  }
  for (auto [k, id]: queries[i]) {
    ans[id] = -L->Query(k);
  }

  // cout << "NODE " << i << ": ";
  // F0R(k, 10) {
  //   cout << L->Query(k) << ' ';
  // }
  // cout << endl;
  // cout << L->pts << endl;

  L->AddLine(0, maxn-2, {1, 0});
  L->InsertLine(0, maxn-2, {0, -1});

  if (L->Query(0) < -1) {
    int lo = 0, hi = maxn-2;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (L->Query(mid) < -1 ? lo : hi) = mid;
    }
    L->pts.insert(hi);
  }

  return L;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // LiChao lc(10);
  // lc.InsertLine(0, 9, {0, 0});
  // // lc.AddLine(0, 0, {1, -3});
  // lc.AddLine(1, 9, {0, 2});
  // // lc.InsertLine(0, 9, Line(3, 5));
  // // lc.InsertLine(0, 9, Line(0, -10));
  // F0R(i, 10) {
  //   cout << lc.Query(i) << ' ';
  // }
  // cout << endl;
  // return 0;
  int N; cin >> N;
  REP(N-1) {
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  int Q; cin >> Q;
  F0R(i, Q) {
    int v, k; cin >> v >> k;
    queries[v].push_back({k, i});
  }
  DFS(1, 1);
  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}
