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
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }

  bool flip = false;
  int mn = *min_element(all(A));
  int mx = *max_element(all(A));
  if (mn == 0 && mx == 0) {
    cout << "No\n";
    return;
  }
  int MX = mx - mn;
  if (-mn > mx) {
    swap(mx, mn);
    mx *= -1, mn *= -1;
    flip = true;
    F0R(i, N) A[i] *= -1;
  }
  vector<int> pos, neg, zeros;
  for (auto x: A) {
    if (x > 0) pos.push_back(x);
    else if (x < 0) neg.push_back(x);
    else zeros.push_back(x);
  }
  sort(all(pos));
  sort(all(neg), greater());

  vector<int> ans;
  int cur = 0;
  while (!pos.empty() || !neg.empty()) {
    if (!pos.empty() && cur + pos.back() <= mx) {
      ans.push_back(pos.back());
      cur += pos.back();
      pos.pop_back();
    }
    else if (!neg.empty() && cur + neg.back() > mn) {
      ans.push_back(neg.back());
      cur += neg.back();
      neg.pop_back();
    }
  }

  F0R(i, sz(zeros)) ans.push_back(0);

  if (flip) {
    for (auto& x: ans) x *= -1;
  }
  cout << "Yes\n";
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
