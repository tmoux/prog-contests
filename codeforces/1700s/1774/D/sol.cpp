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
  vector<string> vs(N);

  int total = 0;
  F0R(i, N) {
    F0R(j, M) {
      char c; cin >> c;
      vs[i] += c;
    }
    for (char c: vs[i]) if (c == '1') total++;
  }

  if (total % N != 0) {
    cout << -1 << '\n';
    return;
  }
  else {
    int target = total / N;
    vector<array<int, 3>> ans;

    vector<tuple<int, int, string>> surplus, deficient;
    F0R(i, N) {
      int cnt = 0;
      for (char c: vs[i]) if (c == '1') cnt++;
      if (cnt > target) surplus.push_back({i, cnt, vs[i]});
      else if (cnt < target) deficient.push_back({i, cnt, vs[i]});
    }

    while (!surplus.empty() && !deficient.empty()) {
      while (!surplus.empty() && get<1>(surplus.back()) == target) {
        surplus.pop_back();
      }
      while (!deficient.empty() && get<1>(deficient.back()) == target) {
        deficient.pop_back();
      }

      if (!surplus.empty() && !deficient.empty()) {
        vector<int> pos;
        auto& [idx1, cnt1, s1] = surplus.back();
        auto& [idx2, cnt2, s2] = deficient.back();
        F0R(j, M) if (s1[j] == '1' && s2[j] != '1') {
          pos.push_back(j);
        }
        // DEBUG(pos);
        while (cnt1-1 >= target && cnt2+1 <= target) {
          int p = pos.back();
          ans.push_back({idx1, idx2, p});
          // cout << "adding " << idx1 << ' ' << idx2 << ' '  << p << endl;
          s1[p] = '0';
          s2[p] = '1';
          cnt1--;
          cnt2++;
          pos.pop_back();
        }
      }
    }

    cout << sz(ans) << '\n';
    for (auto [x, y, z]: ans) {
      cout << x+1 << ' ' << y+1 << ' ' << z+1 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
