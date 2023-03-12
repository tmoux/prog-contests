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

const int maxn = 200005;
int n, t, A[maxn];
ll freq[maxn];
ll sum = 0;

ll ch3(int x) {
  return 1LL * x * (x - 1) * (x - 2) / 6;
}

void update(int x, int d) {
  sum -= ch3(freq[x]);
  freq[x] += d;
  sum += ch3(freq[x]);
}

struct Query
{
  int bucket, l, r, id;

  bool operator<(const Query& rhs) const {
    if (bucket != rhs.bucket) {
      return bucket < rhs.bucket;
    }
    else return r < rhs.r;
  }
};

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  int size = (int)(sqrt(t) + 1);
  vector<Query> queries;
  for (int i = 0; i < t; i++) {
    int l, r; cin >> l >> r;
    queries.push_back({l/size,l,r,i});
  }
  sort(queries.begin(),queries.end());
  vector<ll> ans(t);
  int L = 1, R = 1;
  for (Query q: queries) {
    while (L <= q.l) {
      update(A[L], -1);
      L++;
    }

    while (L > q.l) {
      update(A[L-1], 1);
      L--;
    }

    while (R <= q.r) {
      update(A[R], 1);
      R++;
    }

    while (R > q.r + 1) {
      update(A[R-1], -1);
      R--;
    }
    ans[q.id] = sum;
    //cout << q.l << ' ' << q.r << ' ' << L << ' ' << R << '\n';
  }

  for (int i = 0; i < t; i++) {
    cout << ans[i] << '\n';
  }

  return 0;
}
