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
  ll sum;
  int cnt;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    m = (s+e)/2;
    sum = cnt = 0;
    if (s != e) {
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
      cnt += x < 0 ? -1 : 1;
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
    cnt = l->cnt + r->cnt;
  }

  ll getsum(int st, int en) {
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

  ll firstK(int k) {
    assert(k <= cnt);
    if (s == e) {
      return k == 0 ? 0LL : k * (sum / cnt);
    }
    if (k <= l->cnt) return l->firstK(k);
    else return l->sum + r->firstK(k - l->cnt);
  }
};

ll solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  vector<int> v;
  F0R(i, N) {
    cin >> A[i];
    v.push_back(A[i]);
  }
  Node s1(0, N-1), s2(0, N-1);
  map<int, int> compress;
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) compress[v[i]] = i;
  F0R(i, N) s2.add(compress[A[i]], A[i]);

  auto f = [&](const vector<ll>& v, int k) -> ll {
      if (k > sz(v)) return 1e18;
      else {
          return std::accumulate(v.begin(), v.begin() + k, 0LL);
      }
  };

  ll ans = 1e18;
  F0R(i, N) {
      vector<ll> l, r;
      F0R(j, N) {
          (j <= i ? l : r).push_back(A[j]);
      }
      sort(all(l));
      sort(all(r));
      for (int k = 0; k <= K; k++) {
          ckmin(ans, max(f(l, k), f(r, K-k)));
      }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
