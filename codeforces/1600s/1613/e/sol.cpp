#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) 
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<char>> grid(n, vector<char>(m));
  vector<vector<bool>> poss(n, vector<bool>(m));
  queue<pair<int,int>> q;
  F0R(i, n) {
    F0R(j, m) {
      cin >> grid[i][j];

      if (grid[i][j] == 'L') {
        poss[i][j] = true;
      }
    }
  }

  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};
  auto valid = [&](int i, int j) -> bool {
    return 0 <= i && i < n && 0 <= j && j < m; 
  };
  auto get_adjacents = [&](int i, int j) -> vector<pair<int,int>> {
    vector<pair<int,int>> v;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (valid(ni, nj) && grid[ni][nj] != '#') v.push_back({ni, nj});
    }
    return v;
  };

  F0R(i, n) {
    F0R(j, m) {
      if (grid[i][j] == 'L') {
        for (auto [x, y]: get_adjacents(i, j)) {
          q.push({x, y});
        }
      }
    }
  }

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    //cout << "visiting " << x << ' ' << y << endl;

    int numBad = 0;
    bool canReach = false;
    for (auto [nx, ny]: get_adjacents(x, y)) {
      if (!poss[nx][ny]) numBad++;
      else canReach = true;
    }
    if (canReach && numBad <= 1) {
      poss[x][y] = true;
      for (auto [nx, ny]: get_adjacents(x, y)) {
        if (!poss[nx][ny]) {
          q.push({nx, ny});
        }
      }
    }
  }

  F0R(i, n) {
    F0R(j, m) {
      if (grid[i][j] == '.' && poss[i][j]) {
        cout << '+';
      }
      else cout << grid[i][j];
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
