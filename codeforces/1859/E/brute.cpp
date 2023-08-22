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
    int N, K; cin >> N >> K;
    vector<ll> A(N+1), B(N+1);
    FOR(i, 1, N+1) cin >> A[i];
    FOR(i, 1, N+1) cin >> B[i];

    const ll INF = 1e15;
    vector<vector<ll>> dp(N+1, vector<ll>(N+1, -INF));

    dp[0][0] = 0;
    for (int i = 0; i < N; i++) dp[i][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= i; k++) {
            dp[i][k] = dp[i-1][k];
            for (int j = i-1; j < i && k-(i-j) >= 0; j--) {
                // cout << "checking " << i << ' ' << k << ' ' << j << endl;
                // cout << dp[j][k-(i-j)] << ' ' << abs(A[i] - B[j+1]) << ' ' << abs(B[i] - A[j+1]) << endl;
                ckmax(dp[i][k], dp[j][k-(i-j)] +
                                abs(A[i] - B[j+1]) +
                                abs(B[i] - A[j+1]));
            }
            // cout << i << ' ' << k << ": " << dp[i][k] << endl;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ckmax(ans, dp[i][K]);
        // cout << i << ": " << dp[i][K] << endl;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
}
