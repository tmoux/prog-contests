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

struct Euler {
  typedef vector<pair<int,int>> vpi;
  int N, M;
  vector<vpi> graph; // {ed, edNum}
  vector<vpi::iterator> its;
  vector<bool> used;

  Euler(int _N, int _M) : N(_N), M(_M), graph(N), its(N), used(M) {}

  void add_edge(int i, int j, int id) {
    graph[i].emplace_back(j, id);
    graph[j].emplace_back(i, id);
  }

  vpi eulerPath(int r) {
    F0R(i, N) its[i] = begin(graph[i]);
    F0R(i, M) used[i] = false;
    vpi ans, s{{r, -1}};
    int lst = -1;
    while (sz(s)) {
      int x = s.back().first; auto &it = its[x], en = end(graph[x]);
      while (it != en && used[it->second]) it++;

      if (it == en) {
        if (lst != -1 && lst != x) return {};
        ans.push_back(s.back()); s.pop_back(); if (sz(s)) lst = s.back().first;
      } else {
        s.push_back(*it);
        used[it->second] = 1;
      }
    }
    // check if Euler cycle
    if (sz(ans) != M+1 || ans.front().first != ans.back().first) return {};
    return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<array<int, 2>> A(N);
  F0R(i, N) {
    cin >> A[i][0] >> A[i][1];
  }

  int bestAns = -1;
  vector<int> path;

  for (int k = 20; k >= 0; k--) {
    int ALL = (1 << k) - 1;

    Euler euler(1 << 20, N);
    vector<array<int, 2>> B(N);
    F0R(i, N) {
      B[i][0] = A[i][0] & ALL;
      B[i][1] = A[i][1] & ALL;

      euler.add_edge(B[i][0], B[i][1], i);
      euler.add_edge(B[i][1], B[i][0], i);
    }

    auto p = euler.eulerPath(B[0][0]);
    if (!p.empty()) {
      bestAns = k;
      F0R(i, N) {
        int id = p[i].second;
        if (p[i].first == B[id][0]) {
          path.push_back(2*id);
          path.push_back(2*id+1);
        }
        else {
          path.push_back(2*id+1);
          path.push_back(2*id);
        }
      }
      break;
    }
  }

  cout << bestAns << '\n';
  for (auto i: path) {
    cout << i+1 << ' ';
  }
  cout << '\n';
}
