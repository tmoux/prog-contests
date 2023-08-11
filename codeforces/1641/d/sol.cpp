#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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

const int maxn = 1e5+5;
int N, M;
pair<int, vector<int>> v[maxn];

uint64_t splitmix64(uint64_t x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
size_t hash_vec(const vector<int>& v) {
  size_t r = 0;
  for (auto& x: v) r ^= splitmix64(x + FIXED_RANDOM);
  return r;
}

struct custom_hash {
  size_t operator()(size_t x) const {
    return splitmix64(x + FIXED_RANDOM);
  }
};

vector<pair<size_t, bool>> subs[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    v[i].second.resize(M);
    F0R(j, M) cin >> v[i].second[j];
    cin >> v[i].first;
    sort(all(v[i].second));
  }
  sort(v, v+N);
  F0R(i, N) {
    for (int mask = 1; mask < (1<<M); mask++) {
      vector<int> vec;
      F0R(k, M) if (mask & (1<<k)) {
        vec.push_back(v[i].second[k]);
      }
      subs[i].push_back({hash_vec(vec), sz(vec)%2});
    }
  }
  unordered_map<size_t, int, custom_hash> mp;
  stack<int> st;

  auto upd = [&](int i, int del) -> void {
    for (auto& [h, _]: subs[i]) mp[h] += del;
  };
  auto count_not_disjoint = [&](int i) -> int {
    int cnt = 0;
    for (int mask = 1; mask < (1<<M); mask++) {
      const auto& [h, c] = subs[i][mask-1];
      if (mp.find(h) != mp.end()) {
        cnt += mp[h] * (c?1:-1);
      }
    }
    return cnt;
  };

  int ans = 2e9+1;
  F0R(i, N) {
    while (count_not_disjoint(i) < sz(st)) {
      ckmin(ans, v[i].first + v[st.top()].first);
      upd(st.top(), -1);
      st.pop();
    }
    upd(i, 1);
    st.push(i);
  }
  cout << (ans <= 2e9 ? ans : -1) << '\n';
}
