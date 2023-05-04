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
  int N, M, K; cin >> N >> M >> K;
  map<int, vector<pair<int, int>>> horiz, vert;
  map<int, int> valH, valV;
  F0R(i, K) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) {
      if (y1 > y2) swap(y1, y2);
      horiz[x1].push_back({y1, y2});
    }
    else {
      if (x1 > x2) swap(x1, x2);
      vert[y1].push_back({x1, x2});
    }
  }

  int sum = 0;
  for (auto& [i, v]: horiz) {
    sort(all(v));
    int cur = 0;
    int gap = 0;
    for (auto [l, r]: v) {
      if (l >= cur) {
        gap += l - cur;
      }
      ckmax(cur, r);
    }
    gap += M - cur;
    valH[i] = gap;

    sum ^= valH[i];
  }
  if (N-1 > sz(horiz)) {
    int n = (N - 1) - sz(horiz);
    if (n&1) sum ^= M;
  }

  for (auto& [i, v]: vert) {
    sort(all(v));
    int cur = 0;
    int gap = 0;
    for (auto [l, r]: v) {
      if (l >= cur) {
        gap += l - cur;
      }
      ckmax(cur, r);
    }
    gap += N - cur;
    valV[i] = gap;

    sum ^= valV[i];
  }
  if (M-1 > sz(vert)) {
    int n = (M-1) - sz(vert);
    if (n&1) sum ^= N;
  }

  auto fillgap = [&](int x, vector<pair<int, int>> v) -> int {
    int cur = 0;
    int gap = 0;
    for (auto [l, r]: v) {
      if (l >= cur) {
        if (gap + (l - cur) < x) {
          gap += l - cur;
        }
        else return cur + (x - gap);
      }
      ckmax(cur, r);
    }
    return cur + (x - gap);
  };

  DEBUG(sum);
  if (sum == 0) {
    cout << "SECOND\n";
  }
  else {
    int sh = 0;
    while ((1 << sh) <= sum) sh++;
    sh--;
    auto works = [&](int x) {
      return (1 << sh) & x;
    };
    cout << "FIRST\n";
    if (N-1 > sz(horiz) && works(M)) {
      int i = 1;
      while (horiz.count(i)) i++;
      int x = M - (M ^ sum);
      assert(x > 0);
      int j = fillgap(x, {});
      cout << i << ' ' << 0 << ' ' << i << ' ' << j << '\n';
      goto done;
    }
    for (auto& [i, _]: horiz) {
      if (works(valH[i])) {
        int x = valH[i] - (valH[i] ^ sum);
        assert(x > 0);
        int j = fillgap(x, horiz[i]);
        cout << i << ' ' << 0 << ' ' << i << ' ' << j << '\n';
        goto done;
      }
    }

    if (M-1 > sz(vert) && works(N)) {
      int i = 1;
      while (vert.count(i)) i++;
      int x = N - (N ^ sum);
      assert(x > 0);
      int j = fillgap(x, {});
      cout << 0 << ' ' << i << ' ' << j << ' ' << i << '\n';
      goto done;
    }
    for (auto& [i, _]: vert) {
      if (works(valV[i])) {
        int x = valV[i] - (valV[i] ^ sum);
        DEBUG(valV[i]);
        DEBUG(x);
        assert(x > 0);
        int j = fillgap(x, vert[i]);
        cout << 0 << ' ' << i << ' ' << j << ' ' << i << '\n';
        goto done;
      }
    }
    done:;
  }
}
