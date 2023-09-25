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

vector<pair<int, int>> edges;
vector<array<int, 3>> output;
void add_edge(int i, int j, int k) {
  output.push_back({i, j, k});
}

void rec(int l, int r) {
  int n = (r - l + 1);
  if (n <= 4) return;
  int B = pow(n, 0.5);
  vector<int> v;
  for (int i = l; i <= r; i++) {
    if ((i - l) % B == B-1) v.push_back(i);
  }
  rec(l, v[0]-1);
  for (int i = 0; i + 1 < sz(v); i++) rec(v[i]+1, v[i+1]-1);
  rec(v.back()+1, r);

  for (int i = 0; i < sz(v); i++) {
    for (int j = v[i]-2; j >= (i == 0 ? l : v[i-1]+1); j--) {
      add_edge(j, j+1, v[i]);
    }
    for (int j = v[i]+2; j <= (i+1==sz(v) ? r : v[i+1]-1); j++) {
      add_edge(v[i], j-1, j);
    }
  }

  for (int i = 0; i + 1 < sz(v); i++) {
    add_edge(v[i], v[i+1]-1, v[i+1]);
  }
  for (int d = 2; d < sz(v); d++) {
    for (int i = 0; i + d < sz(v); i++) {
      add_edge(v[i], v[i+d-1], v[i+d]);
    }
  }
}

vector<int> answer(int l, int r, int u, int v) {
  assert(l <= u && u < v && v <= r);
  int n = (r - l + 1);
  if (n <= 3) {
    vector<int> ans;
    for (int i = u; i <= v; i++) {
      ans.push_back(i);
    }
    return ans;
  }
  int B = sqrt(n);

  int uu = (u - l) % B == B-1 ? u : l + (u - l) / B * B + B - 1;
  int vv = (v - l) % B == B-1 ? v : l + (v - l) / B * B - 1;

  if (uu > vv) {
    return answer(max(l, vv+1), min(r, uu-1), u, v);
  }
  else return {u, uu, vv, v};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  rec(0, N);
  cout << sz(output) << endl;
  for (auto [a, b, c]: output) {
    cout << a << ' ' << b << ' ' << c << endl;
  }

  int Q; cin >> Q;
  while (Q--) {
    int u, v; cin >> u >> v;
    auto vec = answer(0, N, u, v);
    sort(all(vec)); vec.erase(unique(all(vec)), vec.end());
    for (auto x: vec) {
      cout << x << ' ';
    }
    cout << endl;
  }

  return 0;
}
