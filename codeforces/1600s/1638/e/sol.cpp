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

const ll INV = 1e18;
const int maxn = 1e6+6;
int n, q;

vector<pair<int,ll>> csum[maxn];

ll colorSum(int c, int a, int b) {
  auto it = upper_bound(all(csum[c]), make_pair(b+1, -INV));
  if (it == csum[c].begin() || prev(it)->first < a) return 0LL;
  else {
    ll R = prev(it)->second;
    auto it2 = upper_bound(all(csum[c]), make_pair(a, -INV));

    if (it2 == csum[c].begin()) return R;
    else {
      ll L = prev(it2)->second;
      return R - L;
    }
  }
}

struct Fenwick // {{{
{
  int n;
  vector<ll> bit;
  Fenwick() {}
  Fenwick(int n_) {
    n = n_ + 1;
    bit.resize(n+1,0);
  }
  void add(int i, ll x) {
    i++;
    for (; i <= n; i += i & (-i))
      bit[i] += x;
  }

  void reset(int i) {
    ll r = sum(i) - sum(i-1);
    add(i, -r);
  }

  ll sum(int i) {
    if (i < 0) return 0LL;
    i++;
    ll r = 0;
    for (; i; i -= i & (-i)) {
      r += bit[i];
    }
    return r;
  }
}; // }}}

int intervalColor[maxn];

struct IntervalManager {
  set<int> active;
  Fenwick fen;

  IntervalManager() {
    fen = Fenwick(q);
    addInterval(0); // initially everyone is color 1
  }

  void recalc(int t) {
    int c = intervalColor[t];
    auto it = active.upper_bound(t);
    int j = it == active.end() ? q : *it-1;
    fen.reset(t);
    fen.add(t, colorSum(c, t, j));
  }

  void addInterval(int t) {
    auto [it, isnew] = active.insert(t);
    assert(isnew);
    
    if (it != active.begin()) recalc(*prev(it));
    recalc(t);
  }

  void removeInterval(int t) {
    auto it = active.find(t);
    assert(it != active.end());
    assert(it != active.begin());
    int p = *prev(it);
    active.erase(it);

    fen.reset(t);
    recalc(p);
  }

  ll query(int t) {
    auto it = active.upper_bound(t);
    assert(it != active.begin());
    ll ans = 0;
    int i = *prev(it);
    int c = intervalColor[i];
    ans += colorSum(c, i, t);
    ans += fen.sum(i-1);
    return ans;
  }
};

vector<int> queries[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> q;

  vector<array<int,2>> begins, ends;
  intervalColor[0] = 1; // initial color is 1
  for (int t = 1; t <= q; t++) {
    string s; cin >> s;
    if (s == "Color") {
      int l, r, c; cin >> l >> r >> c;
      intervalColor[t] = c;
      begins.push_back({l, t});
      ends.push_back({r, t});
    }
    else if (s == "Add") {
      int c, x; cin >> c >> x;
      ll prev = csum[c].empty() ? 0LL : csum[c].back().second;
      csum[c].push_back({t, prev + x});
    }
    else if (s == "Query") {
      int i; cin >> i;
      queries[i].push_back(t);
    }
    else assert(false);
  }

  sort(all(begins)); reverse(all(begins));
  sort(all(ends)); reverse(all(ends));

  vector<ll> ans(q+1, INV);
  IntervalManager manager;
  for (int i = 1; i <= n; i++) {
    // add all new intervals
    while (!begins.empty() && begins.back()[0] == i) {
      int t = begins.back()[1]; begins.pop_back();
      manager.addInterval(t);
    }

    // answer queries
    for (int t: queries[i]) {
      ll q = manager.query(t);
      ans[t] = q;
    }

    // remove all ending intervals
    while (!ends.empty() && ends.back()[0] == i) {
      int t = ends.back()[1]; ends.pop_back();
      manager.removeInterval(t);
    }
  }

  for (int i = 1; i <= q; i++) {
    if (ans[i] != INV) cout << ans[i] << '\n';
  }
}
