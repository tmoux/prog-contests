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

const int maxn = 2e5+5;

template <class S, S (*op)(S, S), S (*e)()>
struct PSeg {
  const int MV = 5000000;
  vector<int> l, r;
  vector<S> sum;
  int nv = 0;
  int rp[maxn];

  PSeg() {
    reset();
  }

  int extend() {
    l.push_back(0);
    r.push_back(0);
    sum.push_back(e());
    return nv++;
  }

  void reset() {
    l.reserve(MV);
    r.reserve(MV);
    sum.reserve(MV);
    l.resize(1, 0);
    r.resize(1, 0);
    sum.resize(1, e());
    nv = 0;
  }

  int build(int tl, int tr) {
    if (tl == tr) return extend();
    int tm = (tl + tr) / 2;
    int cv = extend();
    l[cv] = build(tl, tm);
    r[cv] = build(tm+1, tr);
    sum[cv] = op(sum[l[cv]], sum[r[cv]]);
    return cv;
  }

  S query(int v, int tl, int tr, int L, int R) {
    if (L > R) return e();
    if (L == tl && R == tr) return sum[v];
    int tm = (tl+tr)/2;
    return op(query(l[v], tl, tm, L, min(R, tm)), query(r[v], tm+1, tr, max(L, tm+1), R));
  }

  int update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
      sum[nv] = op(new_val, sum[v]);
      return extend();
    }
    int tm = (tl+tr)/2;
    if (pos <= tm) {
      int cv = extend();
      l[cv] = update(l[v], tl, tm, pos, new_val);
      r[cv] = r[v];
      sum[cv] = op(sum[l[cv]], sum[r[cv]]);
      return cv;
    } else {
      int cv = extend();
      l[cv] = l[v];
      r[cv] = update(r[v], tm+1, tr, pos, new_val);
      sum[cv] = op(sum[l[cv]], sum[r[cv]]);
      return cv;
    }
  }
};

namespace Seg {
  using T = int;
  int op(int a, int b) { return a ^ b; }
  int e() { return 0; }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<int> col(M);
  F0R(i, N) {
    int c; cin >> c; c--;
    col[c] ^= 1;
  }

  int Q; cin >> Q;
  vector<vector<pair<int, int>>> queries(M);
  vector<int> ans(Q);
  F0R(i, Q) {
    int L, R; cin >> L >> R;
    L--, R--;
    queries[L].push_back({R, i});
  }

  PSeg<Seg::T, Seg::op, Seg::e> pseg;
  F0R(k, 19) {
    // reset segtree
    pseg.reset();
    const int MX = 1 << (k+1);
    pseg.rp[0] = pseg.build(0, MX);
    for (int L = M-1; L >= 0; L--) {
      if (col[L]) {
        int idx = (M-1 - L + (1 << k)) % MX;
        int idx2 = (idx + (1 << k));

        pseg.rp[M-L] = pseg.update(pseg.rp[M-L-1], 0, MX, idx, 1);
        if (idx2 <= MX) {
          pseg.rp[M-L] = pseg.update(pseg.rp[M-L], 0, MX, idx2, 1);
        }
        else {
          idx2 -= MX;
          pseg.rp[M-L] = pseg.update(pseg.rp[M-L], 0, MX, 0, 1);
          pseg.rp[M-L] = pseg.update(pseg.rp[M-L], 0, MX, idx2, 1);
        }
      }
      else pseg.rp[M-L] = pseg.rp[M-L-1];

      for (auto [R, id]: queries[L]) {
        int idx = (M-1-L) % MX;
        int d = pseg.query(pseg.rp[M-L], 0, MX, 0, idx) ^
                pseg.query(pseg.rp[M-(R+1)], 0, MX, 0, idx);
        ans[id] ^= d << k;
      }
    }
  }

  F0R(i, Q) {
    cout << (ans[i] ? 'A' : 'B');
  }
  cout << '\n';
}
