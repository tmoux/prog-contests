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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M, P; cin >> N >> M >> P;
  P--;
  vector<pair<ll, int>> v(N);
  F0R(i, N) {
    cin >> v[i].first;
    v[i].second = i;
  }
  sort(all(v));
  vector<int> remap(N);
  F0R(i, N) remap[v[i].second] = i;
  vector<ll> D(N);
  F0R(i, N) D[i] = v[i].first;
  P = remap[P];

  vector<vector<int>> adj(N);
  vector<int> indegree(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    a = remap[a], b = remap[b];
    adj[b].push_back(a);
    indegree[a]++;
  }

  vector<int> In(N);
  vector<bool> hasDep(N, false), reachable(N, false);

  auto check = [&](ll C) -> bool {
    F0R(i, N) {
      In[i] = indegree[i];
      hasDep[i] = reachable[i] = false;
    }
    hasDep[P] = reachable[P] = true;
    F0R(i, N) if (In[i] == 0) hasDep[i] = true;
    queue<int> q; q.push(P);
    int num_visit = 0;

    auto updateDep = [&](int i) -> void {
      hasDep[i] = true;
      if (reachable[i]) {
        q.push(i);
      }
    };

    auto updateReach = [&](int i) -> void {
      reachable[i] = true;
      if (hasDep[i]) {
        q.push(i);
      }
    };

    int lpt = P-1, rpt = P+1;
    ll L = D[P], R = D[P]; // range is [L - C, R + C]
    while (!q.empty()) {
      num_visit++;
      int i = q.front(); q.pop();
      ckmin(L, D[i]);
      ckmax(R, D[i]);

      while (lpt >= 0 && L - C <= D[lpt]) {
        updateReach(lpt--);
      }
      while (rpt < N && D[rpt] <= R + C) {
        updateReach(rpt++);
      }

      for (int j: adj[i]) {
        if (--In[j] == 0) {
          updateDep(j);
        }
      }
    }

    return num_visit == N;
  };

  ll lo = -1, hi = 1e18;
  while (lo + 1 < hi) {
    ll mid = std::midpoint(lo, hi);
    // cout << "check " << mid << ": " << check(mid) << endl;
    (check(mid) ? hi : lo) = mid;
  }
  cout << hi << '\n';
}
