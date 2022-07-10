#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
  template <class Fun>
    class y_combinator_result {
      Fun fun_;

      public:
      template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

      template <class... Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template <class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
!is_same<T_container, string>::value,
  typename T_container::value_type>::type>
  ostream &operator<<(ostream &os, const T_container &v) {
    os << '[';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << ']';
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int solve() {
  int N, M; cin >> N >> M;
  string s, t; cin >> s >> t;

  using State = pair<int, int>;
  map<State, int> dist;
  queue<State> q;
  State init = {(1<<N)-1, N};
  q.push(init);
  dist[init] = 0;

  auto is_end = [&](int mask) -> bool {
    int pt = 0;
    F0R(i, N) {
      if (mask & (1<<i)) {
        if (pt < M && s[i] == t[pt]) {
          pt++;
        }
        else return false;
      }
    }
    return pt == M;
  };

  while (!q.empty()) {
    State s = q.front(); q.pop();
    // cout << "state " << s.first << ' ' << s.second << ": " << dist[s] << endl;
    if (is_end(s.first)) {
      return dist[s];
    }
    else {
      auto go_state = [&](State ns) -> void {
        if (!dist.count(ns)) {
          dist[ns] = dist[s] + 1;
          q.push(ns);
        }
      };
      auto goleft = [&](State s) -> State {
        auto [mask, i] = s;
        while (i > 0) {
          i--;
          if (mask & (1<<i)) break;
        }
        return {mask, i};
      };

      auto goright = [&](State s) -> State {
        auto [mask, i] = s;
        while (i < N) {
          i++;
          if (mask & (1<<(i-1))) break;
        }
        return {mask, i};
      };

      auto gobackspace = [&](State s) -> State {
        s = goleft(s);
        int m = (1<<N) - 1 - (1<<s.second);
        s.first &= m;
        return s;
      };

      go_state({s.first, 0});
      go_state({s.first, N});
      go_state(goleft(s));
      go_state(goright(s));
      if (s.second > 0) go_state(gobackspace(s));
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << endl;
  }
}
