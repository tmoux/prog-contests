#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll
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


int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K, A; cin >> N >> K >> A;
  vector<array<int, 3>> V(N);
  vector<vector<array<int, 2>>> I(K+1);
  vector<int> cost(K+1);
  F0R(i, N) {
    cin >> V[i][0] >> V[i][1] >> V[i][2];
    int d = K - (V[i][0] + V[i][1]);
    int l = V[i][0];
    int r = V[i][0] + d;

    cost[r] += V[i][2];
    // I[i] = {l, r, V[i][2]};
    assert(r <= K);
    I[r].push_back({l, V[i][2]});
  }

  vector<ll> dp(K+1);
  vector<ll> P(K+1);
  Node *seg = new Node(0, K);

  int totalCost = 0;
  for (int i = 0; i <= K; i++) {
    dp[i] = (i == 0 ? 0 : dp[i-1]) + cost[i]; // if take all
    for (auto [l, c]: I[i]) {
      totalCost += c;
      seg->add(l+1, K, c);
      // seg->add(l, l, c);
    }
    P[i] = totalCost;
    // for (int j = 0; j < i; j++) {
    //   cout << seg->getmini(j, j) << ' ';
    // }
    // cout << endl;
    for (int j = 0; j < i; j++) {
      ll upd = A * (i - j) + (P[i] - (j == 0 ? 0 : P[j-1]) - (seg->getmini(i, i) - seg->getmini(j, j))) + (j == 0 ? 0 : dp[j-1]);
      ckmin(dp[i], upd);
      // cout << i << ' ' << j << ": " << upd << endl;
    }
    // cout << endl;
    // cout << i << ": " << dp[i] << endl;
    // if (i > 0) {
    //   ll ci = A * i - totalCost;
    //   DEBUG(ci);
    //   DEBUG(totalCost);
    //   ll mnj = seg->getmini(0, i-1);
    //   DEBUG(mnj);
    //   ckmin(dp[i], ci + mnj);
    //   cout << i << ": " << dp[i] << endl;
    // }

    // update i
    // ll newVal = (i == 0 ? 0 : dp[i-1]) - A * i + totalCost;
    // ll cur = seg->getmini(i, i);
    // seg->add(i, i, newVal - cur);
  }

  cout << dp[K] << '\n';
}
