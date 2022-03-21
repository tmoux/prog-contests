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

const int maxn = 5e5+5;
int a[maxn];
bool start[maxn];

int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  int K = 1;
  vector<pair<int,int>> v;
  REP(Q) {
    int l, r; cin >> l >> r;
    if (l == r) continue;
    ckmax(K, r-l+1);
    v.push_back({l, r});
  }
  if (v.empty()) {
    cout << K << '\n';
    for (int i = 1; i <= N; i++) {
      cout << 1 << " \n"[i==N];
    }
  }
  else {
    sort(all(v));
    pair<int,int> cur = {v[0].first, v[0].second};
    vector<pair<int,int>> u;
    for (auto [l, r]: v) {
      if (l > cur.second) {
        u.push_back(cur);
        cur = {l, r};
      }
      else {
        ckmax(cur.second, r);
      }
    }
    u.push_back(cur);
    for (auto [l, r]: u) {
      a[l]++;
      a[r+1]--;
      start[l] = true;
    }

    int c = 1;
    for (int i = 1; i <= N; i++) {
      a[i] += a[i-1];
      if (i == 1 || a[i] == 0 || start[i]) {
        ans[i] = c;
      }
      else {
        ++c; if (c > K) c = 1;
        ans[i] = c;
      }
    }
    cout << K << '\n';
    for (int i = 1; i <= N; i++) {
      cout << ans[i] << " \n"[i==N];
    }
  }

}
