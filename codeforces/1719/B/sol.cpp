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
  int N, k; cin >> N >> k;
  k %= 4;
  if (k == 0) {
    cout << "NO\n";
  }
  else if (N == 2) {
    if (k == 1) {
      cout << "YES\n";
      cout << "1 2\n";
    }
    else if (k == 2) {
      cout << "YES\n";
      cout << "2 1\n";
    }
    else {
      cout << "YES\n";
      cout << "1 2\n";
    }
  }
  else {
    vector<int> rem(N+1, 1);
    vector<int> fours;
    for (int i = 4; i <= N; i += 4) {
      fours.push_back(i);
      rem[i] = 0;
    }
    vector<int> as;
    FOR(i, 1, N+1) {
      if ((i + k) % 4 == 0) {
        as.push_back(i);
        rem[i] = 0;
      }
    }

    vector<pair<int, int>> ans;

    if (sz(fours) + sz(as) < N/2) {
      assert(k != 2);
      vector<int> evens, aas;
      for (int i = 1; i <= N; i++) {
        if ((i + k) % 2 == 0 && rem[i]) {
          aas.push_back(i);
        }
      }

      for (int i = 2; i <= N; i++) {
        if (rem[i]) {
          evens.push_back(i);
        }
      }

      while (sz(ans) + sz(fours) + sz(as) < N/2) {
        assert(!evens.empty());
        assert(!aas.empty());
        int a = aas.back(); aas.pop_back();
        int b = evens.back(); evens.pop_back();
        rem[a] = rem[b] = 0;
        ans.push_back({a, b});
      }
    }

    int i = 1;
    for (int b: fours) {
      while (!rem[i]) i++;
      assert(i <= N);
      ans.push_back({i, b});
      rem[i] = 0;
    }
    for (int a: as) {
      while (!rem[i]) i++;
      assert(i <= N);
      ans.push_back({a, i});
      rem[i] = 0;
    }

    assert(sz(ans) == N/2);


    cout << "YES\n";
    for (auto [a, b]: ans) {
      assert((1LL * (a + k) * b) % 4 == 0);
      cout << a << ' ' << b << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
