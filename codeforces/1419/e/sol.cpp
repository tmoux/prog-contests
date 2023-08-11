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
  int X = N;
  map<int, int> cnt;
  vector<int> divisors = {N};
  for (int i = 2; i*i <= N; i++) {
    while (X % i == 0) {
      cnt[i]++;
      X /= i;
    }
    if (N % i == 0) {
      divisors.push_back(i);
      if (N/i != i) divisors.push_back(N/i);
    }
  }
  if (X > 1) cnt[X]++;

  vector<pair<int, int>> v;
  for (auto p: cnt) v.push_back(p);

  if (sz(v) == 2) {
    if (v[0].second == 1 && v[1].second == 1) {
      cout << v[0].first << ' ' << v[1].first << ' ' << N << '\n';
      cout << 1 << '\n';
    }
    else {
      auto check = [](const vector<int>& v) -> bool {
        F0R(i, sz(v)) {
          int a = v[i];
          int b = v[(i+1)%sz(v)];
          if (__gcd(a, b) == 1) return false;
        }
        return true;
      };
      while (true) {
        shuffle(all(divisors), rng);
        if (check(divisors)) {
          for (auto d: divisors) {
            cout << d << ' ';
          }
          cout << '\n' << 0 << '\n';
          return;
        }
      }
    }
  }
  else {
    set<int> S;
    F0R(i, sz(v)) {
      int p = v[i].first;
      int q = v[(i+1)%sz(v)].first;
      S.insert(p);
      S.insert(p*q);
    }
    map<int, vector<int>> mp;
    for (auto d: divisors) {
      if (S.count(d)) continue;
      for (auto [p, _]: v) {
        if (d % p == 0) {
          mp[p].push_back(d);
          break;
        }
      }
    }
    F0R(i, sz(v)) {
      int p = v[i].first;
      int q = v[(i+1)%sz(v)].first;
      cout << p << ' ';
      for (auto d: mp[p]) cout << d << ' ';
      cout << p*q << ' ';
    }
    cout << '\n' << 0 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
