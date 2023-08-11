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

const int maxn = 1e5+5;
const int maxk = 30;
int p[maxn], a[maxn];
int jmp[maxk][maxn];

int in[maxn];

int endup[maxn];

int walk(int i, int M) {
  for (int k = maxk-1; k >= 0; k--) {
    if (M & (1<<k)) {
      i = jmp[k][i];
    }
  }
  return i;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  FOR(i, 1, n+1) {
    cin >> p[i];
    in[p[i]]++;
    jmp[0][i] = p[i];
  }
  for (int k = 1; k < maxk; k++) {
    FOR(i, 1, n+1) {
      jmp[k][i] = jmp[k-1][jmp[k-1][i]];
    }
  }
  int mx = 0;
  FOR(i, 1, n+1) {
    cin >> a[i];
    ckmax(mx, a[i]);
  }
  int K = 0;
  queue<int> q;
  FOR(i, 1, n+1) {
    if (in[i] == 0) {
      K++;
      q.push(i);
    }
  }
  assert((mx - n) % K == 0);
  int M = (mx - n) / K;

  FOR(i, 1, n+1) {
    endup[i] = walk(i, M);
  }

  vector<vector<int>> poss_indices(n+1);
  vector<int> ans(n+1, -1);
  vector<bool> chosen(n+1, false);
  FOR(i, 1, n+1) {
    poss_indices[endup[i]].push_back(i);
  }

  vector<pair<int,int>> vec;
  FOR(i, 1, n+1) {
    if (a[i] <= n) {
      assert(!poss_indices[i].empty());
      sort(all(poss_indices[i]));
      ans[poss_indices[i][0]] = a[i];
      chosen[a[i]] = true;
      for (int j = 1; j < sz(poss_indices[i]); j++) {
        vec.push_back({a[i], poss_indices[i][j]});
      }
    }
  }
  sort(all(vec), greater<pair<int,int>>());

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; i++) {
    if (!chosen[i]) {
      while (!vec.empty() && vec.back().first < i) {
        pq.push(vec.back().second); 
        vec.pop_back();
      }
      assert(!pq.empty());
      int y = pq.top(); pq.pop();
      ans[y] = i;
    }
  }

  FOR(i, 1, n+1) {
    cout << ans[i] << " \n"[i==n];
  }
  return 0;
}
