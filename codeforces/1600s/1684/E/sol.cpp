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
  int sum;
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

  void add(int i, int x) {
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

  int getsum(int st, int en) {
    if (st > en) return 0;
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

  int walk(int x) { // returns min i s.t. sum(0, i) > x
    if (s == e) return s;
    else if (l->sum > x) return l->walk(x);
    else return r->walk(x - l->sum);
  }
};

void solve() {
  int N, K; cin >> N >> K;
  map<int, int> cnt;
  F0R(i, N) {
    int x; cin >> x;
    cnt[x]++;
  }
  vector<pair<int, int>> vs;
  for (auto [x, y]: cnt) {
    vs.push_back({y, x});
  }
  sort(all(vs));
  N = sz(vs);
  map<int, int> toIndex;
  F0R(i, N) {
    toIndex[vs[i].second] = i;
  }

  Node *seg1 = new Node(0, N-1);
  F0R(i, N) {
    seg1->add(i, vs[i].first);
  }
  Node *seg2 = new Node(0, N-1);
  F0R(i, N) {
    seg2->add(i, 1);
  }

  int ans = N;
  {
    int mex = 0;
    while (cnt.count(mex)) mex++;
    ckmin(ans, sz(cnt) - mex);
  }
  for (int mex = 0, x = 0, extra = 0; x <= K; mex++) {
    if (seg1->sum + extra < x) break;
    else {
      int diff;
      if (seg1->sum <= x) {
        diff = sz(cnt) + x - seg2->sum;
      }
      else {
        int idx = seg1->walk(x);
        diff = sz(cnt) + x - seg2->getsum(0, idx-1);
      }

      // cout << mex << ": " << diff << ' ' << (diff-(mex+1)) << endl;

      ckmin(ans, diff-mex);
    }

    if (cnt.count(mex)) {
      seg1->add(toIndex[mex], -cnt[mex]);
      seg2->add(toIndex[mex], -1);
      extra += cnt[mex] - 1;
    }
    else {
      x++;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
