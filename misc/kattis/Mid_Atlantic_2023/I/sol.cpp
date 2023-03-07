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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  using vi = vector<int>;
  vector<vi> t(N+1);
  F0R(i, N+1) {
    REP(3) {
      int x; cin >> x;
      if (x) t[i].emplace_back(x);
    }
  }

  vector<pair<int, int>> ans;
  // move from tube i to j
  auto move = [&](int i, int j) {
    assert(!t[i].empty() && sz(t[j]) < 3);
    ans.emplace_back(i, j);
    t[j].push_back(t[i].back());
    t[i].pop_back();
  };

  auto make_empty = [&]() -> int {
    vector<int> v;
    F0R(i, N+1) {
      if (t[i].empty()) return i;
      if (sz(t[i]) < 3) v.push_back(i);
    }
    sort(all(v), [&](int i, int j) {
      return sz(t[i]) < sz(t[j]);
    });
    if (sz(v) == 3) {
      move(v[0], v[1]);
      move(v[0], v[2]);
      return v[0];
    }
    else if (sz(v) == 2) {
      move(v[0], v[1]);
      return v[0];
    }
    else assert(false);
  };

  // Favors indices where top color appears twice.
  auto find_index = [&]() -> int {
    F0R(i, N+1) {
      if (t[i].empty() || (t[i][0] == t[i][1] && t[i][1] == t[i][2])) continue;
      if (t[i][2] == t[i][0] || t[i][2] == t[i][1]) return i;
    }
    F0R(i, N+1) {
      if (t[i].empty() || (t[i][0] == t[i][1] && t[i][1] == t[i][2])) continue;
      return i;
    }
    return -1;
  };

  auto find_color_index = [&](int color, vector<int> v) -> int {
    F0R(i, N+1) {
      if (find(all(v), i) != v.end()) continue;
      if (find(all(t[i]), color) != t[i].end()) return i;
    }
    assert(false);
  };

  auto fix_bottom = [&](int& i, int& empty) -> void {
    REP(3) {
      move(i, empty);
    }
    swap(i, empty);
  };

  auto fix_middle = [&](int i, int j, int empty) -> void {
    move(i, empty);
    move(j, empty);
    move(j, i);
    move(empty, j);
    move(i, j);
    move(empty, i);
  };

  auto make_monochrome = [&](int i, int j, int k, int empty) -> void {
    move(i, empty);
    move(j, empty);
    move(k, empty);
  };

  // fix tube like 1 _ 1
  //               _ _ 1
  // in 4 moves
  auto make_monochrome_special = [&](int i, int j, int empty) -> void {
    move(i, empty);
    move(j, empty);
    move(i, j);
    move(i, empty);
  };

  // fix tube like _ 1 1
  //               _ _ 1
  // in 3 moves
  auto make_monochrome_special2 = [&](int i, int j, int empty) -> void {
    move(i, empty);
    move(i, empty);
    move(j, empty);
  };

  // General strategy: Repeatedly remove a color in less than 20 moves.
  // - At the start of each round, make one tube empty if there isn't one already.
  // - Pick a nonempty tube that isn't fixed yet and select its top color.
  // - Find the other locations of the same color, and move them to the top of their tubes.
  // - Move all three of the color to empty tube.
  // Actually this construction only takes at most 17N moves, and on the test data the bound is even lower.
  while (true) {
    int empty = make_empty(); // 2
    int i = find_index();
    if (i == -1) break;
    int color = t[i].back();

    if (t[i][0] == color || t[i][1] == color) {
      int j = find_color_index(color, {i});
      if (t[j][0] == color) fix_bottom(j, empty); // 3
      else if (t[j][1] == color) fix_middle(i, j, empty); // 6

      if (t[i][0] == color)
        make_monochrome_special(i, j, empty); // 4
      else
        make_monochrome_special2(i, j, empty); // 3
    }
    else {
      int j = find_color_index(color, {i});
      if (t[j][0] == color && t[j][1] == color) {
        // Special case
        fix_bottom(j, empty); // 3
        make_monochrome_special2(j, i, empty); // 3
      }
      else {
        int k = find_color_index(color, {i, j});
        if (t[j][0] == color) fix_bottom(j, empty); // 3
        else if (t[j][1] == color) fix_middle(i, j, empty); // 6

        if (t[k][0] == color) fix_bottom(k, empty); // 3
        else if (t[k][1] == color) fix_middle(i, k, empty); // 6

        make_monochrome(i, j, k, empty); // 3
      }
    }
  }

  F0R(i, N+1) {
    assert(t[i].empty() || (sz(t[i]) == 3 && t[i][0] == t[i][1] && t[i][1] == t[i][2]));
  }
  assert(sz(ans) <= 17 * N);
  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << a+1 << ' ' << b+1 << '\n';
  }
}
