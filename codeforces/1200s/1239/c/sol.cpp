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

const int maxn = 1e5+5;
int N, P;
ll T[maxn], ans[maxn];

set<int> line, waiting;
queue<pair<ll, int>> q;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> P;
  vector<pair<ll, int>> v;
  F0R(i, N) {
    cin >> T[i];
    v.emplace_back(T[i], i);
  }
  sort(all(v), greater());

  auto can_add_queue = [&](int i) {
    return line.empty() || i < *line.begin();
  };
  auto add_to_queue = [&](int i) {
    line.insert(i);
    q.emplace(P, i);
  };
  auto add_to_waiting = [&](int i) {
    waiting.insert(i);
  };
  ll curt = 0;
  auto rem_from_queue = [&]() {
    auto [t, i] = q.front(); q.pop();
    curt += t;
    ans[i] = curt;
    line.erase(i);
  };
  while (!v.empty() || !q.empty()) {
    if (v.empty()) {
      rem_from_queue();
    }
    else {
      auto [t, i] = v.back();
      if (q.empty()) {
        v.pop_back();
        ll d = t - curt;
        curt += d;
        add_to_queue(i);
      }
      else {
        auto& [p, j] = q.front();
        if (curt + p < t) {
          rem_from_queue();
        }
        else {
          v.pop_back();
          ll d = t - curt;
          curt += d;
          p -= d;
          // if i can go directly onto the queue, do that
          if (can_add_queue(i)) {
            add_to_queue(i);
          }
          else {
            add_to_waiting(i);
          }
        }
      }
    }

    // check if we can add someone from waiting
    if (!waiting.empty()) {
      int i = *waiting.begin();
      if (can_add_queue(i)) {
        waiting.erase(i);
        add_to_queue(i);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] << " \n"[i == N-1];
  }
}
