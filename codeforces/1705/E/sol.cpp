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
  int lazy;
  int mini;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = 0;
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
    if (s != e) {
      l->lazy += lazy;
      l->sum += (l->e - l->s + 1) * lazy;

      r->lazy += lazy;
      r->sum += (r->e - r->s + 1) * lazy;
    }
    lazy = 0;
  }

  void add(int st, int en, int x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy += x;
      sum += (e - s + 1) * x;
      return;
    }
    push();
    if (st <= m) {
      l->add(st,en,x);
    }
    if (en > m) {
      r->add(st,en,x);
    }
    sum = l->sum + r->sum;
  }

  int getsum(int st, int en) {
    push();
    //if completely included
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

  int highestIndexWithSum(int x) {
    if (s == e) return sum == x ? s : -1;
    push();
    cout << s << ' ' << e << ": " << l->sum << ' ' << r->sum << ' ' << x << endl;
    if (l->sum <= x) {
      int idx = r->highestIndexWithSum(x - l->sum);
      return idx != -1 ? idx : l->highestIndexWithSum(x);
    }
    else return l->highestIndexWithSum(x);
  }

  int lowestIndexWithSum(int x) {
    if (s == e) return sum == x ? s : -1;
    push();
    if (l->sum >= x) return l->lowestIndexWithSum(x);
    else return r->lowestIndexWithSum(x - l->sum);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  const int maxn = 2e5 + 20;
  Node* seg1 = new Node(0, maxn);
  Node* seg2 = new Node(0, maxn);
  seg2->add(0, maxn, 1);

  auto add = [&](int i) {
    if (seg1->getsum(i, i) == 0) {
      seg1->add(i, i, 1);
      seg2->add(i, i, -1);
    }
    else {
      int idx = seg2->lowestIndexWithSum(seg2->getsum(0, i) + 1);
      seg1->add(i, idx-1, -1);
      seg2->add(i, idx-1, 1);
      seg1->add(idx, idx, 1);
      seg2->add(idx, idx, -1);
    }
  };

  auto sub = [&](int i) {
    if (seg1->getsum(i, i) == 1) {
      seg1->add(i, i, -1);
      seg2->add(i, i, 1);
    }
    else {
      int idx = seg1->lowestIndexWithSum(seg1->getsum(0, i) + 1);
      seg1->add(i, idx-1, 1);
      seg2->add(i, idx-1, -1);
      seg1->add(idx, idx, -1);
      seg2->add(idx, idx, 1);
    }
  };

  int N, Q; cin >> N >> Q;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    add(A[i]);
  }

  while (Q--) {
    int k, x; cin >> k >> x;
    k--;
    sub(A[k]);
    A[k] = x;
    add(A[k]);

    cout << seg1->lowestIndexWithSum(seg1->getsum(0, maxn)) << '\n';
  }
}
