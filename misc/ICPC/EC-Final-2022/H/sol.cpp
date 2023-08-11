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

const int MX = 40;
const int ROWS = 17;
array<int, 2> upl[MX][MX], upr[MX][MX], downl[MX][MX], downr[MX][MX];
int mxR[ROWS+1] = {0, 1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1};
pair<int, int> st[ROWS+1] = {
{0, 0},
{0, 0},
{1, 0},
{1, 0},
{1, 0}, // 4
{5, 0},
{1, 1},
{1, 1},
{1, 1},
{1, 1},
{1, 0},
{1, 0},
{1, 0},
{1, 0},
{1, 5},
{1, 1},
{1, 1},
{1, 1},
};

void add_upl(int a, int b, int c, int d) {
  upl[a][b] = {c, d};
  if (d >= 0) downr[c][d] = {a, b};
}
void add_upr(int a, int b, int c, int d) {
  upr[a][b] = {c, d};
  if (d >= 0) {
    downl[c][d] = {a, b};
  }
}
void init() {
  for (int i = 2; i <= ROWS; i++) {
    for (int j = st[i].first; j <= mxR[i]; j++) {
      int d = j - st[i].first;
      add_upl(i, j, i-1, st[i].second + d);
      add_upr(i, j, i-1, st[i].second + d + 1);
    }
  }
}

bool valid(array<int, 2> p) {
  auto [i, j] = p;
  return 1 <= i && i <= ROWS && 1 <= j && j <= mxR[i];
}

int cv(int i, int j) {
  return (i-1) * MX + (j-1);
}

void solve() {
  int N; cin >> N;
  vector<array<int, 2>> v(N);
  vector<int> on(MX*MX);
  F0R(i, N) {
    cin >> v[i][0] >> v[i][1];
    on[cv(v[i][0], v[i][1])] = 1;
  }
  int ans = 0;
  for (auto [x, y]: v) {
    vector<bool> vis(MX*MX);
    on[cv(x, y)] = 0;
    int add = 0;
    queue<array<int, 2>> q;
    vis[cv(x, y)] = 1;
    q.push({x, y});

    auto tryjump = [&](const vector<array<int, 2>>& d) -> void {
      int j = sz(d);
      for (int jj = 1; jj < sz(d); jj++) {
        auto [a, b] = d[jj];
        if (on[cv(a, b)]) {
          j = jj;
          break;
        }
      }
      int k = sz(d);
      for (int kk = j+1; kk < sz(d); kk++) {
        auto [a, b] = d[kk];
        if (on[cv(a, b)]) {
          k = kk;
          break;
        }
      }
      if (2*j < k) {
        auto [a, b] = d[2*j];
        if (!vis[cv(a, b)]) {
          vis[cv(a, b)] = 1;
          q.push({a, b});
        }
      }
    };

    // cout << x << ' ' << y << ": " << endl;
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      // cout << "(" << i << ' ' << j << ")" << "  ";
      add++;
      // RIGHT
      int a = i, b = j;
      vector<array<int, 2>> d = {{i, j}};
      while (b+1 <= mxR[a]) {
        b++;
        d.push_back({a, b});
      }
      tryjump(d);

      // LEFT
      a = i, b = j; d = {{i, j}};
      while (b-1 >= 1) {
        b--;
        d.push_back({a, b});
      }
      tryjump(d);

      auto set = [&](int& a, int& b, array<int, 2> p) {
        a = p[0];
        b = p[1];
      };
      // UPLEFT
      a = i, b = j; d = {{i, j}};
      while (valid(upl[a][b]) && upl[a][b][0] != 0) {
        set(a, b, upl[a][b]);
        // tie(a, b) = upl[a][b];
        d.push_back({a, b});
      }
      tryjump(d);

      // UPRIGHT
      a = i, b = j; d = {{i, j}};
      while (valid(upr[a][b]) && upr[a][b][0] != 0) {
        set(a, b, upr[a][b]);
        // tie(a, b) = upr[a][b];
        d.push_back({a, b});
      }
      tryjump(d);

      // DOWNLEFT
      a = i, b = j; d = {{i, j}};
      while (valid(downl[a][b]) && downl[a][b][0] != 0) {
        set(a, b, downl[a][b]);
        // tie(a, b) = downl[a][b];
        d.push_back({a, b});
      }
      tryjump(d);

      // DOWNRIGHT
      a = i, b = j; d = {{i, j}};
      while (valid(downr[a][b]) && downr[a][b][0] != 0) {
        set(a, b, downr[a][b]);
        // tie(a, b) = downr[a][b];
        d.push_back({a, b});
      }
      tryjump(d);
    }
    ans += add - 1;
    on[cv(x, y)] = 1;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init();
  int T; cin >> T;
  while (T--) solve();
}
