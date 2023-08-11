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

const int maxn = 1e6 + 6;
int N;
vector<int> adj[maxn];

template<int M = 1>
ll knapsack(const vector<int>& sizes, int sz) {
  if (sz > M) {
    return knapsack<min(2*M, maxn)>(sizes, sz);
  }
  bitset<M+1> ret; ret[0] = 1;
  for (auto x: sizes) ret |= ret << x;

  ll ans = 0;
  for (int i = 0; i <= sz; i++) {
    if (ret[i]) ckmax(ans, 1LL * i * (sz - i));
  }
  return ans;
}

ll get_closest(const vector<int>& sizes, int sz) {
  if (sizes.empty()) return 0;
  if (sizes.back() * 2 >= sz) return 1LL * sizes.back() * (sz - sizes.back());

  vector<int> bsizes;
  int cnt = 0;
  F0R(i, sz(sizes)) {
    cnt++;
    if (i == sz(sizes) - 1 || sizes[i] != sizes[i+1]) {
      int j = 1;
      while (j < cnt) {
        bsizes.push_back(sizes[i] * j);
        cnt -= j;
        j *= 2;
      }
      bsizes.push_back(sizes[i] * cnt);
      cnt = 0;
    }
  }
  return knapsack(bsizes, sz);
}

pair<ll, int> dfs(int i) {
  ll sum = 0;
  int sz = 0;
  vector<int> sizes;
  for (int j: adj[i]) {
    auto [sumj, szj] = dfs(j);
    sum += sumj;
    sz += szj;
    sizes.push_back(szj);
  }

  sort(all(sizes));
  ll add = get_closest(sizes, sz);

  return {sum + add, sz + 1};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  FOR(i, 2, N+1) {
    int p; cin >> p;
    adj[p].push_back(i);
  }

  cout << dfs(1).first << '\n';
}
