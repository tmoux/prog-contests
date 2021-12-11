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

const int n = 10;
int g[n][n];
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  F0R(i, n) {
    string s; cin >> s;
    F0R(j, n) {
      g[i][j] = s[j]-'0';
    }
  }

  int ans = 0;
  int iter = 1;
  while (true) {
    cout << "iter: " << iter++ << endl;
    queue<pair<int,int>> q;
    bool marked[n][n];
    memset(marked, false, sizeof marked);
    F0R(i, n) {
      F0R(j, n) {
        g[i][j]++;
        if (g[i][j] > 9) {
          q.push({i, j});
          marked[i][j] = true;
        }
      }
    }

    int flashes = 0;

    auto adj = [&](int x, int y) -> vector<pair<int,int>> {
      vector<pair<int,int>> ret;
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          if (dx == 0 && dy == 0) continue;
          int nx = x + dx;
          int ny = y + dy;
          if (0 <= nx && nx < n && 0 <= ny && ny < n) {
            ret.push_back({nx, ny});
          }
        }
      }
      return ret;
    };

    while (!q.empty()) {
      auto [x, y] = q.front(); q.pop();
      flashes++;
      marked[x][y] = true;
      for (auto [nx, ny]: adj(x, y)) {
        g[nx][ny]++;
      }
      for (auto [nx, ny]: adj(x, y)) {
        if (g[nx][ny] > 9 && !marked[nx][ny]) {
          marked[nx][ny] = true;
          q.push({nx, ny});
        }
      }
    }

    F0R(i, n) {
      F0R(j, n) {
        if (g[i][j] > 9) {
          g[i][j] = 0;
        }
      }
    }
    ans += flashes;

    bool sync = true;
    F0R(i, n) {
      F0R(j, n) {
        if (g[i][j] != 0) sync = false;
      }
    }
    if (sync) {
      cout << "SYNC" << endl;
      break;
    }
  }
}
