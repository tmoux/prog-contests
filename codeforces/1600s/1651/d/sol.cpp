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

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};

int dist(array<int, 2> a, array<int, 2> b) {
  return abs(a[0]-b[0]) + abs(a[1]-b[1]);
}
vector<array<int, 2>> adj(array<int, 2> p) {
  vector<array<int, 2>> ret;
  F0R(k, 4) {
    int nx = p[0] + dx[k];
    int ny = p[1] + dy[k];
    ret.push_back({nx, ny});
  }
  return ret;
}

const int maxn = 2e5+5;
int n;

map<array<int, 2>, int> s;
array<int, 2> p[maxn], ans[maxn];
bool vis[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  F0R(i, n) {
    cin >> p[i][0] >> p[i][1];
    s[p[i]] = i;
  }

  queue<int> q;
  F0R(i, n) {
    bool found = false;
    for (auto pt: adj(p[i])) {
      if (!s.count(pt)) {
        found = true;
        ans[i] = pt;
      }
    }
    if (found) {
      vis[i] = true;
      q.push(i);
    }
  }
  while (!q.empty()) {
    int i = q.front(); q.pop();
    for (auto pt: adj(p[i])) {
      if (s.count(pt)) {
        int j = s[pt];
        if (!vis[j]) {
          ans[j] = ans[i];
          vis[j] = true;
          q.push(j);
        }
      }
    }
  }
  F0R(i, n) {
    cout << ans[i][0] << ' ' << ans[i][1] << '\n';
  }
}
