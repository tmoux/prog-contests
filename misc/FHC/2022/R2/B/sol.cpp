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

const int MOD = 1e9+7;

struct Client {
  int A, B, X, Y, id;

  bool operator<(const Client& rhs) const {
    return X < rhs.X;
  }
};

struct TopK {
  int K;
  multiset<ll> ms;

  TopK(int _K) {
    K = _K;
  }

  void insert(ll P, int Y) {
    ms.insert(P - Y);
    while (sz(ms) > K) {
      ms.erase(ms.begin());
    }
  }

  vector<ll> get_top(int X) {
    vector<ll> r;
    for (auto x: ms) r.push_back(X + x);
    return r;
  }
};

int solve() {
  int N, K; cin >> N >> K;

  map<int, vector<Client>> clientStarts;
  vector<Client> clients(N);
  F0R(i, N) {
    cin >> clients[i].A >> clients[i].B >> clients[i].X >> clients[i].Y;
    clients[i].id = i;
    clientStarts[clients[i].A].push_back(clients[i]);
  }

  map<int, vector<pair<int, ll>>> endings;

  vector<ll> profits;
  for (auto& [start, v]: clientStarts) {
    sort(all(v));
    sort(all(endings[start]));
    int i = 0;

    TopK topk(K);
    for (Client c: v) {
      while (i < sz(endings[start]) && endings[start][i].first < c.X) {
        topk.insert(endings[start][i].second, endings[start][i].first);
        i++;
      }

      // cout << "Client " << c.id+1 << endl;
      auto tops = topk.get_top(c.X);
      // cout << tops << endl;
      for (auto P: tops) {
        profits.push_back(P);
        endings[c.B].push_back({c.Y, P});
      }
      // add starting one with no profit
      // if (tops.empty()) {
      endings[c.B].push_back({c.Y, 0LL});
      // }
    }
  }

  sort(all(profits), greater<ll>());
  ll ans = 0;
  for (int i = 0; i < min(sz(profits), K); i++) {
    ans = (ans + profits[i]) % MOD;
  }

  // cout << profits << endl;

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
