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

struct Node {
  int s, e, m;
  //covers s,e;
  ll sum;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    if (s != e) {
      m = (s+e)/2;
      l = new Node(s,m);
      r = new Node(m+1,e);
    }
    else {
      l = nullptr;
      r = nullptr;
    }
  }

  void add(int i, ll x) {
    if (s == e) {
      sum += x;
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
  }

  ll getsum(int st, int en) {
    if (st > en) return 0;
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

struct LazyNode {
  int s, e, m;
  //covers s,e;
  ll sum;
  ll lazy;
  pair<ll, int> mini;
  LazyNode *l, *r;

  LazyNode(int a, int b) {
    s = a;
    e = b;
    sum = 1e9;
    lazy = 0;
    mini = {1e9, s};
    if (s != e) {
      m = (s+e)/2;
      l = new LazyNode(s,m);
      r = new LazyNode(m+1,e);
      pull();
    }
    else {
      l = NULL;
      r = NULL;
    }
  }

  void pull() {
    sum = l->sum + r->sum;
    mini = min(l->mini,r->mini);
  }

  void push() {
    if (s != e) {
      l->lazy += lazy;
      l->sum += (l->e - l->s + 1) * lazy;
      l->mini.first += lazy;

      r->lazy += lazy;
      r->sum += (r->e - r->s + 1) * lazy;
      r->mini.first += lazy;
    }
    lazy = 0;
  }

  void add(int st, int en, ll x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy += x;
      sum += (e - s + 1) * x;
      mini.first += x;
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

  pair<ll, int> getmini(int st, int en) {
    push();
    //if completely included
    if (st <= s && e <= en) {
      return mini;
    }
    pair<ll, int> ret = {1000000000000000000, -1};
    if (st <= m) {
      ret = min(ret,l->getmini(st,en));
    }
    if (en > m) {
      ret = min(ret,r->getmini(st,en));
    }
    return ret;
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

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  vector<pair<int, int>> v;
  F0R(i, N) {
    cin >> A[i];
    v.push_back({A[i], i});
  }
  sort(all(v));

  map<pair<int, int>, int> toIndex;
  F0R(i, N) toIndex[v[i]] = i;

  Node seg1(0, N-1), seg2(0, N-1), seg3(0, N-1);
  ll total = 0;
  ll weighted_sum = 0;
  map<int, int> mp;
  mp[-1] = 0;
  LazyNode lseg(0, N-1);
  F0R(i, N) {
    total += A[i];
    int idx = toIndex[{A[i], i}];
    auto it = mp.upper_bound(idx);
    int val = A[i] - prev(it)->second;
    seg1.add(idx, val);
    if (it != mp.end()) {
      int j = it->first;
      seg1.add(j, -val);
    }
    mp[idx] = A[i];
    ll sum = seg1.getsum(0, idx);
    seg3.add(idx, 1);
    int sum2 = seg2.getsum(0, idx);
    if (sum > sum2) {
      seg2.add(idx, 1);
      ll weight = seg3.getsum(idx, N-1);
      weighted_sum += weight;

      ll x = lseg.getsum(idx, idx);
      lseg.add(idx, idx, -x + sum - sum2);
      lseg.add(idx, N-1, -1);

      if (idx + 1 < N) {
        auto [mn, j] = lseg.getmini(idx + 1, N-1);
        assert(mn >= -1);
        if (mn == -1) {
          ll weight = seg3.getsum(j, N-1);
          weighted_sum -= weight;
          seg2.add(j, -1);
          lseg.add(j, N-1, 1);
        }
      }
    }
    weighted_sum += seg2.getsum(0, idx-1);
    ll ans = total - weighted_sum;
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
