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
  ll lazy;
  ll mini;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = 0;
    mini = 0;
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
      l->mini += lazy;

      r->lazy += lazy;
      r->sum += (r->e - r->s + 1) * lazy;
      r->mini += lazy;
    }
    lazy = 0;
  }

  void add(int st, int en, ll x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy += x;
      sum += (e - s + 1) * x;
      mini += x;
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
    mini = min(l->mini,r->mini);
  }

  ll getmini(int st, int en) {
    push();
    //if completely included
    if (st <= s && e <= en) {
      return mini;
    }
    ll ret = 1000000000000000000;
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

const int maxn = 2e5+5;
int N, Q;
string S;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q >> S;

  set<int> sA, sB;
  auto checkA = [&](int i) {
    if (i+1 < N && S[i] == '(' && S[i+1] == '(') {
      sA.insert(i);
    }
    else if (sA.count(i)) sA.erase(i);
  };
  auto checkB = [&](int i) {
    if (i > 0 && S[i] == ')' && S[i-1] == ')') {
      sB.insert(i);
    }
    else if (sB.count(i)) sB.erase(i);
  };

  Node seg(0, N);
  F0R(i, N) {
    int d = S[i] == '(' ? 1 : -1;
    seg.add(i, N, d);
    checkA(i);
    checkB(i);
  }

  auto update = [&](int i) -> void {
    S[i] = S[i] == '(' ? ')' : '(';
    int d = S[i] == '(' ? 1 : -1;
    seg.add(i, N, 2*d);
    checkA(i-1); checkA(i);
    checkB(i); checkB(i+1);
  };

  REP(Q) {
    int i; cin >> i;
    i--;
    update(i);
    // cout << S << endl;
    // cout << sA << ' ' << sB << endl;

    bool p = false;
    if (N % 2 == 0 && S[N-1] == ')') {
      int sum = seg.getsum(N-1, N-1);
      // DEBUG(sum);
      if (sum == 0 && seg.getmini(0, N-1) >= 0) {
        p = true;
      }
      else {
        bool canReach = false;
        if (seg.getmini(0, N-1) >= 0) canReach = 1;
        {
          if (!sA.empty()) {
            int i = *sA.begin();
            if (seg.getmini(0, i) >= 0) canReach = 1;
          }
        }
        int idx = -1;
        if (!sB.empty()) idx = *sB.rbegin();
        int s = idx == -1 ? 0 : seg.getsum(idx, idx);
        bool isBal = idx == N-1 || (seg.getsum(N-1, N-1) == s && seg.getmini(idx+1, N-1) == s);

        if (canReach && isBal) p = 1;
      }
    }

    cout << (p ? "YES" : "NO") << '\n';
  }
}
