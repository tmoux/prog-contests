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
int N, A[maxn];
vector<int> adj[maxn];

const int B = 5;
int dp[maxn][1<<B];
int f(int i, int p, int cur) {
    int& res = dp[i][cur];
    if (res != -1) return res;
    if (i != p && sz(adj[i]) == 1) {
        return res = A[i] == cur ? 0 : 1;
    }

    res = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        res += f(j, i, cur ^ A[i]);
    }

    F0R(d, 1 << B) {
        int tr = 1;
        for (int j: adj[i]) {
            if (j == p) continue;
            tr += f(j, i, d);
        }
        ckmin(res, tr);
    }
    return res;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    F0R(i, N) cin >> A[i];
    REP(N-1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(dp, -1, sizeof dp);
    cout << f(0, 0, 0) << '\n';
}
