#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  int getsz(int i) {
    return -par[Find(i)];
  }
};

void solve() {
  int N, M; cin >> N >> M;
  DSU dsu(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    dsu.Union(a, b);
  }
  vector<int> C;
  F0R(i, N) {
    if (i == dsu.Find(i)) {
      C.push_back(dsu.getsz(i));
    }
  }
  sort(all(C), greater());
  DEBUG(C);

  bool poss = false;
  vector<pair<int, int>> F;
  set<vector<pair<int, int>>> S;
  auto rec = y_combinator([&](auto rec, int K, int sum, int n) -> void {
    if (poss) return;
    if (n == K) {
      poss = true;
      return;
    }
    int T = N / K;
    if (sum == T) {
      rec(K, 0, n+1);
    }
    else {
      if (S.count(F)) return;
      S.insert(F);
      for (int i = 0; i < sz(F); i++) {
        for (int j = 1; j <= F[i].second && sum + j * F[i].first <= T; j++) {
          F[i].second -= j;

          rec(K, sum + j * F[i].first, n);

          F[i].second += j;
        }
      }
    }
  });


  auto check = [&](int K, vector<int> C) -> bool {
    poss = false;
    cerr << "check " << K << ": " << poss << endl;
    map<int, int> mp;
    for (auto x: C) mp[x]++;
    S.clear();
    F.clear();
    for (auto [a, b]: mp) F.emplace_back(a, b);
    rec(K, 0, 0);
    return poss;
    // int T = N / K;
    // vector<bool> used(sz(C), false);
    // REP(K) {
    //   int cur = 0;
    //   F0R(i, sz(C)) {
    //     if (!used[i] && cur + C[i] <= T) {
    //       used[i] = true;
    //       cur += C[i];
    //     }
    //   }
    //   if (cur != T) return false;
    // }
    // return true;
  };

  vector<int> ans;
  for (int K = 1; K <= N; K++) {
    if (N / K >= C[0] && N % K == 0) {
      if (check(K, C)) ans.push_back(K);
    }
  }

  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": ";
    solve();
  }
}
