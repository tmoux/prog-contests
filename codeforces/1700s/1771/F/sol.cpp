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
// persistent segtree {{{
const int MV = 5000000;
int l[MV], r[MV];
int sum[MV];
int nv = 0;
int rp[maxn];
int M; // size of segtree = # of distinct elements

int build(int tl, int tr) {
  if (tl == tr) return nv++;
  int tm = (tl + tr) / 2;
  int cv = nv;
  nv++;
  l[cv] = build(tl, tm);
  r[cv] = build(tm+1, tr);
  sum[cv] = sum[l[cv]] ^ sum[r[cv]];
  return cv;
}

int query(int v, int tl, int tr, int L, int R) {
  if (L > R) return 0;
  if (L == tl && R == tr) return sum[v];
  int tm = (tl+tr)/2;
  return query(l[v], tl, tm, L, min(R, tm)) ^ query(r[v], tm+1, tr, max(L, tm+1), R);
}

int update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    sum[nv] = new_val ^ sum[v];
    return nv++;
  }
  int tm = (tl+tr)/2;
  if (pos <= tm) {
    int cv = nv; nv++;
    l[cv] = update(l[v], tl, tm, pos, new_val);
    r[cv] = r[v];
    sum[cv] = sum[l[cv]] ^ sum[r[cv]];
    return cv;
  } else {
    int cv = nv; nv++;
    l[cv] = l[v];
    r[cv] = update(r[v], tm+1, tr, pos, new_val);
    sum[cv] = sum[l[cv]] ^ sum[r[cv]];
    return cv;
  }
}

int smallestNonzeroPrefixRec(int v1, int v2, int tl, int tr) {
  if (tl == tr) {
    return tl;
  }
  int tm = (tl+tr)/2;
  if (sum[l[v1]] ^ sum[l[v2]]) {
    return smallestNonzeroPrefixRec(l[v1], l[v2], tl, tm);
  }
  else {
    return smallestNonzeroPrefixRec(r[v1], r[v2], tm+1, tr);
  }
}

int smallestNonzeroPrefix(int L, int R) {
  // returns smallest index i such that the xor of all elements with index
  // <= i in the range [L, R] is nonzero
  // return -1 is no such index
  if (sum[rp[R]] ^ sum[rp[L-1]])
    return smallestNonzeroPrefixRec(rp[L-1], rp[R], 0, M-1);
  else return -1;
}
// }}}

int N;
int A[maxn], R[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  map<int, vector<int>> indices;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    indices[A[i]].push_back(i);
  }

  M = sz(indices);
  map<int, int> mpToX, mpToIndex;
  int t = 0;
  for (auto [c, _]: indices) {
    mpToX[c] = rng();
    R[t] = c;
    mpToIndex[c] = t++;
  }

  rp[0] = build(0, M-1);
  for (int i = 1; i <= N; i++) {
    rp[i] = update(rp[i-1], 0, M-1, mpToIndex[A[i]], mpToX[A[i]]);
  }

  int ans = 0;
  int Q; cin >> Q;
  REP(Q) {
    int l, r; cin >> l >> r;
    l ^= ans, r ^= ans;
    // cout << "l = " << l << ", r = " << r << endl;

    int i = smallestNonzeroPrefix(l, r);
    ans = i == -1 ? 0 : R[i];

    cout << ans << '\n';
  }
}
