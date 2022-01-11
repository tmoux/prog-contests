#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

const int maxn = 2005;
const ll INF = 1e18;

int n, k;

vector<pair<int,int>> v;
ll dp[maxn][maxn];
int s = -1;

ll f(int i, int j) {
  if (j == s) return 0LL;
  if (i >= n) return INF;
  ll& res = dp[i][j];  
  if (res != -1) return res;

  res = f(i+1, j);
  if (v[i].first <= j+1) {
    ckmin(res, f(i+1, j+1) + v[i].second);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k;
  vector<int> w(n), d(n);
  F0R(i, n) {
    cin >> w[i] >> d[i];
  }

  if (k == 1) {
    F0R(i, n) {
      v.push_back({d[i], w[i]});
    }
    sort(all(v));
    for (int size = n; size >= 0; size--) {
      bool poss = true;
      for (int i = 0; i < size; i++) {
        if (i+1 > v[n-size+i].first) {
          poss = false;
          break;
        }
      }
      if (poss) {
        s = size;
        break;
      }
    }
    memset(dp, -1, sizeof dp);
    ll sum = f(0, 0);
    assert(s != -1);
    cout << s << ' ' << sum << '\n';
  }
  else if (n <= 20) {
    vector<pair<int,ll>> valid;
    for (int mask = 0; mask < (1<<n); mask++) {
      bool can = true;
      vector<pair<int,int>> v;
      for (int i = 0; i < n; i++) {
        if (mask & (1<<i)) {
          v.push_back({d[i], w[i]});
        }
      }
      sort(all(v));
      ll sum = 0;
      for (int i = 0; i < sz(v); i++) {
        if (i+1 > v[i].first) {
          can = false;
          break;
        }
        else sum += v[i].second;
      }
      if (can) {
        valid.push_back({sz(v), sum});
      }
    }
    sort(all(valid), [](auto a, auto b) {
        if (a.first != b.first) return a.first > b.first;
        else return a.second < b.second;
        });
    for (int i = 0; i < k; i++) {
      cout << valid[i].first << ' ' << valid[i].second << '\n';
    }
  }
  else assert(false);
}
