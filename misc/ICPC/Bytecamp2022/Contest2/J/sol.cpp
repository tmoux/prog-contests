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

const int maxn = 20;
int N;
ll K;
int A[maxn][maxn];

const ll INF = 1e18;

ll mss(const vector<ll>& v) {
  ll ans = -INF, mn = 0, sum = 0;
  for (ll x : v) {
    sum += x;
    ckmax(ans, sum - mn);
    ckmin(mn, sum);
  }
  return ans;
}

ll max_suffix_sum(const vector<ll>& v) {
  ll ans = -INF, sum = 0;
  for (int i = sz(v)-1; i >= 0; i--) {
    sum += v[i];
    ckmax(ans, sum);
  }
  return ans;
}

vector<pair<ll, ll>> prefixes[maxn], suffixes[maxn];

void dfs(int i, int j, vector<ll>& v) { // {{{
  v.push_back(A[i][j]);
  if (i + j == N - 1) {
    ll max_subarray = mss(v); 
    ll max_suffix = max_suffix_sum(v);
    if (max_subarray <= K) {
      prefixes[i].push_back({max_suffix, max_subarray});
    }
  }
  else {
    if (i+1 < N) dfs(i+1, j, v);
    if (j+1 < N) dfs(i, j+1, v);
  }

  v.pop_back();
}

void dfs2(int i, int j, vector<ll>& v) {
  if (i + j == N - 1) {
    ll max_subarray = mss(v); 
    ll max_prefix = max_suffix_sum(v);
    if (max_subarray <= K) {
      suffixes[i].push_back({max_prefix, max_subarray});
    }
  }
  else {
    v.push_back(A[i][j]);
    if (i-1 >= 0) dfs2(i-1, j, v);
    if (j-1 >= 0) dfs2(i, j-1, v);
    v.pop_back();
  }

} // }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N) {
    F0R(j, N) {
      cin >> A[i][j];
    }
  }

  vector<ll> v;  
  dfs(0, 0, v);
  dfs2(N-1, N-1, v);

  ll ans = 0;
  F0R(i, N) {
    sort(all(prefixes[i])); reverse(all(prefixes[i]));
    sort(all(suffixes[i]));

    int pt1 = 0;
    int num_subarray_sum_K = 0;

    int pt2 = 0;
    map<ll, int> mp;
    for (auto [suf, k]: prefixes[i]) {
      while (pt1 < sz(suffixes[i]) && suf + suffixes[i][pt1].first < K) {
        if (suffixes[i][pt1].second == K) num_subarray_sum_K++;
        pt1++;
      }
      while (pt2 < sz(suffixes[i]) && suf + suffixes[i][pt2].first <= K) {
        mp[suffixes[i][pt2].first]++;
        pt2++;
      }

      if (k == K) {
        ans += pt2;
      }
      else {
        ans += num_subarray_sum_K; // # < K, with subarray sum K
        ans += mp[K-suf]; // # = K, with any subarray sum
      }
    }
  }
  cout << ans << '\n';
}
