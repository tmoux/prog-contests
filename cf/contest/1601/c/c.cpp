#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

int n, m;
const int S = 1<<20;
struct node {
	long long sum, pref;
	node(long long sum, long long pref) : sum(sum), pref(pref) {}
	node(long long x = 0) : sum(x), pref(x) {}
	friend node operator+(const node& a, const node& b) {
		return {a.sum + b.sum, min(a.pref, a.sum + b.pref)};
	}
} tt[S << 1];

void build(int k = 1, int l = 1, int r = n) {
	if (l == r) { tt[k] = node(1); return; }
	int m = (l + r) >> 1;
	build(k << 1, l, m);
	build(k << 1 | 1, m + 1, r);
	tt[k] = tt[k << 1] + tt[k << 1 | 1];
}

void update(int i, int x, int k = 1, int l = 1, int r = n) {
	if (l == r) { tt[k] = node(x); return; }
	int m = (l + r) >> 1;
	if (i <= m) update(i, x, k << 1, l, m);
	else update(i, x, k << 1 | 1, m + 1, r);
	tt[k] = tt[k << 1] + tt[k << 1 | 1];
}

node query(int ql, int qr, int k = 1, int l = 1, int r = n) {
	if (ql > r || qr < l) return 0;
	if (ql <= l && qr >= r) return tt[k];
	int m = (l + r) >> 1;
	node q1 = query(ql, qr, k << 1, l, m);
	node q2 = query(ql, qr, k << 1 | 1, m + 1, r);
	return q1 + q2;
}

struct Fenwick/*{{{*/
{
    int n;
    vector<int> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, int x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    int sum(int i) {
        int r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

ll countInversions(int n, vector<int> a) {/*{{{*/
  map<int, vector<int>> as;
  for (int i = 1; i <= n; i++) {
    as[a[i]].push_back(i);
  }
  Fenwick fen(n);
  ll inversions = 0;
  for (auto [ai, v]: as) {
    for (int i: v) {
      inversions += fen.sum(n) - fen.sum(i-1);
    }
    for (int i: v) {
      fen.add(i, 1);
    }
  }
  return inversions;
}/*}}}*//*}}}*/

ll solve() {
  cin >> n >> m;
  vector<int> a(n+1), b(m+1);
  vector<pair<int,int>> as;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    as.push_back({a[i], i});
  }
  sort(all(as));

  map<int,int> mpb;
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    mpb[b[i]]++;
  }

  build(1, 1, n);

  ll numInversions = 0;
  int numSmaller = 0;
  int pt = 0;
  for (auto [bi, cnt]: mpb) {
    while (pt < as.size() && as[pt].first < bi) {
      auto [ai, i] = as[pt]; pt++;
      update(i, -1);
      numSmaller++;
    }
    vector<int> bs;
    while (pt < as.size() && as[pt].first == bi) {
      auto [ai, i] = as[pt]; pt++;
      update(i, 0);
      bs.push_back(i);
    }

    ll add = 1LL * cnt * (numSmaller + min(0LL, query(1, n).pref));
    numInversions += add;

    for (int i: bs) {
      update(i, -1);
      numSmaller++;
    }
  }

  numInversions += countInversions(n, a);
  return numInversions;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
