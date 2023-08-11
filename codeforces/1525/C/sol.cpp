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

void solve() {
  int N, M; cin >> N >> M;
  vector<int> ans(N, -1);
  vector<int> pos(N);
  F0R(i, N) cin >> pos[i];
  vector<char> dir(N);
  F0R(i, N) cin >> dir[i];

  vector<array<int, 3>> odds, evens;
  F0R(i, N) {
    (pos[i]&1 ? odds : evens).push_back({pos[i], dir[i] == 'L' ? 0 : 1, i});
  }

  auto LL = [&](int i, int j) -> int {
    assert(i < j);
    return i + (j - i) / 2;
  };
  auto RR = [&](int i, int j) -> int {
    assert(i < j);
    return (M - j) + (j - i) / 2;
  };
  auto LR = [&](int i, int j) -> int {
    assert(i < j);
    if (i < (M - j)) {
      return i + RR(0, j + i);
    }
    else {
      return (M - j) + LL(i - (M - j), M);
    }
  };
  auto RL = [&](int i, int j) -> int {
    assert(i < j);
    return (j - i) / 2;
  };

  auto F = [&](vector<array<int, 3>> v) {
    sort(all(v));
    // cout << v << endl;
    // 0 = L, 1 = R
    deque<array<int, 3>> deq;
    for (auto [x, d, id]: v) {
      if (d == 1) {
        deq.push_back({x, d, id});
      }
      else {
        if (!deq.empty() && deq.back()[1] == 1) {
          auto [xi, di, idi] = deq.back(); deq.pop_back();
          int t = RL(xi, x);
          ans[idi] = ans[id] = t;
        }
        else {
          deq.push_back({x, d, id});
        }
      }
    }
    // cout << deq << endl;
    while (sz(deq) >= 2 && deq[0][1] == 0 && deq[1][1] == 0) {
      auto [xi, di, idi] = deq.front(); deq.pop_front();
      auto [xj, dj, idj] = deq.front(); deq.pop_front();
      ans[idi] = ans[idj] = LL(xi, xj);
    }

    while (sz(deq) >= 2 && deq[sz(deq)-1][1] == 1 && deq[sz(deq)-2][1] == 1) {
      auto [xj, dj, idj] = deq.back(); deq.pop_back();
      auto [xi, di, idi] = deq.back(); deq.pop_back();
      ans[idi] = ans[idj] = RR(xi, xj);
    }

    if (sz(deq) == 2) {
      auto [xi, di, idi] = deq.front();
      auto [xj, dj, idj] = deq.back();
      ans[idi] = ans[idj] = LR(xi, xj);
    }
  };

  F(odds);
  F(evens);

  F0R(i, N) {
    cout << ans[i] << " \n"[i == N-1];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
