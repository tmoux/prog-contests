#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

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

// }}}

void solve(int R, int G, int B) {
  int N = R + G + B;
  if (B <= R + G) {
    vector<char> color(N);
    vector<pair<int,int>> edges;

    auto set_color = [&](int i, char c) {
      color[i] = c;
    };
    auto add_edge = [&](int u, int v) {
      edges.push_back({u, v});
    };

    int pt = 0;
    set_color(pt++, 'R');
    REP(G) {
      int g = pt++;
      set_color(g, 'G');
      add_edge(0, g);
    }
    REP(R-1) {
      int r = pt++;
      set_color(r, 'R');
      add_edge(1, r);
    }
    F0R(i, B) {
      int b = pt++;
      set_color(b, 'B');
      add_edge(i, b);
    }

    F0R(i, N) {
      cout << color[i];
    }
    cout << '\n';
    assert(sz(edges) == N-1);
    for (auto [u, v]: edges) {
      cout << u+1 << ' ' << v+1 << '\n';
    } 
  }
  else {
    cout << -1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int R, G, B; cin >> R >> G >> B;
    solve(R, G, B);
  }
}
