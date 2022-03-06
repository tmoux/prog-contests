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

struct Node {/*{{{*/
  int s, e, m;
  //covers s,e;
  int sum;
  int maxi;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    maxi = 0;
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

  void add(int i, int x) {
    if (s == e) {
      sum += x;
      maxi = sum;
      return;
    }
    if (i <= m) {
      l->add(i,x);
    }
    else if (i > m) {
      r->add(i,x);
    }
    else assert(false);
    sum = l->sum + r->sum;
    maxi = max(l->maxi,r->maxi);
  }

  int getmaxi(int st, int en) {
    if (st <= s && e <= en) {
      return maxi;
    }
    int ret = 0;
    if (st <= m) {
      ret = max(ret,l->getmaxi(st,en));
    }
    if (en > m) {
      ret = max(ret,r->getmaxi(st,en));
    }
    return ret;
  }	

  int getsum(int st, int en) {
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
};/*}}}*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int INF = 1e9;
  int n, q;
  cin >> n >> q;

  vector<array<int,2>> queries;
  vector<array<int,3>> sick;
  vector<array<int,2>> starts, ends;

  F0R(i, q) {
    int t; cin >> t;
    if (t == 0) {
      int l, r, x; cin >> l >> r >> x;
      if (x == 0) {
        starts.push_back({l, i});
        ends.push_back({r, i});
      }
      else {
        sick.push_back({l, r, i});
      }
    }
    else {
      int j; cin >> j;
      queries.push_back({j, i});
    }
  }

  sort(all(starts)); reverse(all(starts));
  sort(all(ends)); reverse(all(ends));

  vector<int> earliest(n+1, INF);
  set<int> times;
  set<int> sickIndices;
  for (int i = 1; i <= n; i++) {
    while (!starts.empty() && starts.back()[0] == i) {
      times.insert(starts.back()[1]);
      starts.pop_back();
    }

    if (!times.empty()) earliest[i] = *times.begin();
    else sickIndices.insert(i);

    while (!ends.empty() && ends.back()[0] == i) {
      times.erase(ends.back()[1]);
      ends.pop_back();
    }
  }

  Node *earliestSeg = new Node(1, n);
  for (int i = 1; i <= n; i++) {
    earliestSeg->add(i, earliest[i]);
  }

  vector<int> discoverSick(n+1, INF);
  for (auto [l, r, t]: sick) {
    auto it = sickIndices.lower_bound(l);
    if (it != sickIndices.end() && *it <= r && 
        (next(it) == sickIndices.end() || *next(it) > r)) {
      int i = *it;
      int tr = t;
      if (l <= i-1) ckmax(tr, earliestSeg->getmaxi(l, i-1));
      if (i+1 <= r) ckmax(tr, earliestSeg->getmaxi(i+1, r));
      ckmin(discoverSick[i], tr);
    }
  }

  for (auto [i, t]: queries) {
    if (sickIndices.count(i)) {
      cout << (t < discoverSick[i] ? "N/A" : "YES") << '\n';
    }
    else {
      cout << (t < earliest[i] ? "N/A" : "NO") << '\n';
    }
  }
}
