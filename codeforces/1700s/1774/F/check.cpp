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

  int N = 10;
  vector<int> v;
  for (int i = 1; i <= N; i++) {
    int n = sz(v);
    v.resize(2 * n);
    copy_n(v.begin(), n, v.begin() + n);
    v.push_back(i);
  }
  cout << v << endl;

  auto count_less = [&](int i, int x) {
    int c = 0;
    int j = 0;
    for (; j < sz(v); j++) {
      if (v[j] == i) c++;
      if (c == x) break;
    }

    vector<int> cnt(N + 1), cnt2(N + 1);
    for (int k = 0; k < sz(v); k++) cnt2[v[k]]++;
    for (int k = 0; k <= j; k++) {
      cnt[v[k]]++;
      cnt2[v[k]]--;
    }

    for (int k = 1; k <= N; k++) {
      cout << k << ": " << cnt[k] << ' ' << cnt2[k] << endl;
    }
  };

  while (true) {
    int i, x; cin >> i >> x;
    count_less(i, x);
  }


  /*
  int N; cin >> N;
  vector<pair<int, int>> A(N);
  F0R(i, N) {
    cin >> A[i].first;
    if (A[i].first != 3) cin >> A[i].second;
  }
  vector<vector<pair<int, int>>> blocks;
  {
    vector<pair<int, int>> v;
    F0R(i, N) {
      if (A[i].first == 3) {
        blocks.push_back(v);
        v.clear();
      }
      else {
        v.push_back(A[i]);
      }
    }
    blocks.push_back(v);
  }
  int K = sz(blocks);
  vector<ll> totalSub(K);
  F0R(i, K) {
    for (auto [op, x]: blocks[i]) {
      if (op == 2) {
        totalSub[i] += x;
      }
    }
  }
  */
}
