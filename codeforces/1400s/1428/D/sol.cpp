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
  vector<int> A(N);
  vector<pair<int, int>> ans;
  F0R(i, N) {
    cin >> A[i];
  }

  set<int> open, taken1;
  set<pair<int, int>> cols;
  F0R(i, N) {
    open.insert(i);
  }
  bool poss = true;

  const int INF = 2e9;
  F0Rd(i, N) {
    if (A[i] == 0) {
      continue;
    }
    else if (A[i] == 1) {
      if (!open.empty()) {
        int r = *open.begin();
        open.erase(open.begin());
        ans.push_back({r, i});
        taken1.insert(r);
        cols.insert({r, i});
      }
      else poss = false;
    }
    else if (A[i] == 2) {
      if (!taken1.empty()) {
        int r = *taken1.begin();
        taken1.erase(taken1.begin());
        ans.push_back({r, i});
        cols.insert({-INF, i});
      }
      else poss = false;
    }
    else if (A[i] == 3) {
      if (!cols.empty() && !open.empty()) {
        auto [rr, j] = *cols.begin();
        cols.erase(cols.begin());

        int r = *open.begin();
        open.erase(open.begin());
        ans.push_back({r, i});
        ans.push_back({r, j});

        cols.insert({-INF, i});
        if (taken1.count(rr)) taken1.erase(rr);
      }
      else poss = false;
    }
    else assert(false);
  }

  if (!poss) {
    cout << -1 << '\n';
    return 0;
  }

  // vector<string> G(N, string(N, '.'));
  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << N-a << ' ' << b+1 << '\n';
    // G[N-1-a][b] = '#';
  }

  // F0R(i, N) {
  //   cout << G[i] << endl;
  // }
}
