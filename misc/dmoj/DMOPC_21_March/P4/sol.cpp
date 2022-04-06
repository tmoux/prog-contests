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

template<typename T>
struct Fenwick
{
    int n;
    vector<T> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, T x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    T sum(T i) {
        T r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

const int maxn = 2e5+5;
int N, Q;



int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  vector<pair<int,int>> v, u;
  F0R(i, N) {
    int a, b; cin >> a >> b;
    v.push_back({a-b, a});
  }

  vector<int> mxIndexL(N), mxIndexR(N);
  vector<ll> sum(N, 0);
  auto recalc = [&]() {
    u = v; sort(all(u)); reverse(all(u));
    F0R(i, N) {
      sum[i] = max(0, u[i].first) + (i > 0 ? sum[i-1] : 0);
    }

    pair<int,int> mx = {-2e9, -1};
    F0R(i, N) {
      ckmax(mx, {u[i].second-u[i].first, i});
      mxIndexL[i] = mx.second;
    }
    mx = {-2e9, -1};
    F0Rd(i, N) {
      ckmax(mx, {u[i].second, i});
      mxIndexR[i] = mx.second;
    }
  };

  recalc();

  auto check = [&](int k, ll R) {
    int idx = mxIndexL[k-1];
    ll t1 = sum[k-1] + (u[idx].second - u[idx].first);
    ll t2 = 0;
    if (k > 1) {
      idx = mxIndexR[k-1];
      t2 = sum[k-2] + u[idx].second;
    }
    return max(t1, t2) >= R;
  };

  cin >> Q;
  REP(Q) {
    int t; cin >> t;
    if (t == 0) {
      int R; cin >> R;
      if (!check(N, R)) {
        cout << -1 << '\n';
      }
      else {
        int lo = 0, hi = N;
        while (lo + 1 < hi) {
          int mid = (lo+hi)/2;
          (check(mid, R) ? hi : lo) = mid;
        }
        cout << hi << '\n';
      }
    }
    else {
      int x, y; cin >> x >> y;
      v[t-1] = {x-y, x};
      recalc();
    }
  }
}
