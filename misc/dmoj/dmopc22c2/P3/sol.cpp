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

const int maxn = 5e5+5;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

set<int> getPrimes(int X) {
  set<int> s;
  while (X > 1) {
    s.insert(spf[X]);
    X /= spf[X];
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  int N; cin >> N;
  vector<int> A(N);

  vector<int> indegree(N+1, 0);
  vector<int> pos(N+1);

  map<int, vector<int>> primes;
  F0R(i, N) {
    cin >> A[i];
    pos[A[i]] = i;

    auto s = getPrimes(A[i]);
    for (auto p: s) {
      primes[p].push_back(i);
    }
  }
  vector<vector<int>> adj(N+1);

  auto nextIndex = [&](set<int> s, int i) {
    int idx = N;
    for (int p: s) {
      auto it = upper_bound(all(primes[p]), i);
      if (it != primes[p].end()) ckmin(idx, *it);
    }
    return idx;
  };

  for (int i = 0; i < N; i++) {
    int X = A[i];
    auto s = getPrimes(X);
    int j = i;
    while (!s.empty()) {
      j = nextIndex(s, j);
      if (j == N) break;

      adj[A[i]].push_back(A[j]);
      indegree[A[j]]++;

      vector<int> remove;
      for (auto p: s) {
        if (A[j] % p == 0) {
          remove.push_back(p);
        }
      }
      for (auto p: remove) s.erase(p);
    }
  }

  priority_queue<int> pq;
  for (int i = 1; i <= N; i++) {
    if (indegree[i] == 0) {
      pq.push(i);
    }
  }

  vector<int> order;
  while (!pq.empty()) {
    int i = pq.top(); pq.pop();
    order.push_back(i);
    for (int j: adj[i]) {
      if (--indegree[j] == 0) {
        pq.push(j);
      }
    }
  }

  F0R(i, N) {
    cout << order[i] << " \n"[i==N-1];
  }
}
