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

ll N, X;
int Y;
ll ans = 0;
vector<int> v;
bool ispal(const vector<int>& v) {
    auto u = v; reverse(all(u));
    return u == v;
}
bool check() {
    vector<int> u;
    F0R(i, N/2) u.push_back(v[i]);
    return ispal(v) && ispal(u);
}

void rec(ll i, ll cur_sum, int cur_y, ll xx) {
    if (i == N) {
        if (cur_sum == X && cur_y == Y) {
            if (check()) {
                for (auto x: v) {
                    cout << std::bitset<4>(x) << ' ';
                }
                cout << '\n';
                // cout << v << endl;
                ans ^= xx;
            }
        }
        return;
    }
    for (ll x = 0; cur_sum + x <= X; x++) {
        int ncur_y = cur_y | x;
        if ((ncur_y & Y) == ncur_y) {
            v.push_back(x);
            rec(i+1, cur_sum + x, ncur_y, xx ^ x);
            v.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> X >> Y;
    rec(0, 0, 0, 0);
    cout << ans << '\n';
    /*
    N = 7, Y = 15;
    for (int i = 14; i <= 75; i++) {
        X = i;
        ans = 0;
        rec(0, 0, 0, 0);
        cout << N << ' ' << X << ' ' << Y << ": " << ans << endl;
    }
    */
}
