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

const int maxn = 3e5+5;
int freq[maxn];

void update(int x, int d) {
  freq[x] += d;
}

struct Query
{
  int bucket, l, r, k, id;

  bool operator<(const Query& rhs) const {
    if (bucket != rhs.bucket) {
      return bucket < rhs.bucket;
    }
    else return r < rhs.r;
  }
};

int N, Q, A[maxn];
vector<int> v[maxn];
int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  FOR(i, 1, N+1) {
    cin >> A[i];
  }

  vector<Query> queries;
  int size = (int)(sqrt(Q) + 1);
  F0R(i, Q) {
    ans[i] = 1e9;
    int l, r, k;
    cin >> l >> r >> k;
    queries.push_back({l/size, l, r, k, i});
  }
  sort(all(queries));

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
    const int B = 100;
    uniform_int_distribution<int> dist(q.l, q.r);
    int target = (q.r - q.l + 1) / q.k + 1;
    REP(B) {
      int i = dist(rng);
      if (freq[A[i]] >= target) {
        ckmin(ans[q.id], A[i]);
      }
    }
  }

  F0R(i, Q) {
    cout << (ans[i] < 1e9 ? ans[i] : -1) << '\n';
  }
}
