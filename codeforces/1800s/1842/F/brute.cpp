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

const int maxn = 5005;
int N;
vector<int> adj[maxn];
int A[maxn];

int cnt = 0;
int ans = 0;
int dfs(int i, int p) {
    int c = A[i];
    for (int j: adj[i]) {
        if (j == p) continue;
        int k = dfs(j, i);
        ans += abs(k-(cnt-k));
        c += k;
    }
    return c;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    REP(N-1) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dp(N+1, 0);
    F0R(mask, 1 << N) {
        cnt = 0;
        FOR(i, 1, N+1) {
            if (mask & (1 << (i-1))) {
                A[i] = 1;
                cnt++;
            }
            else A[i] = 0;
        }
        ans = 0;
        dfs(1, 1);
        ckmax(dp[cnt], ans);

        int oldans = ans;
        ans = 0;
        cnt = cnt + 2;
        dfs(1, 1);
        // if (cnt-2 == 3) cout << mask << ' ' << cnt << ": " << oldans << ' ' << ans << endl;
    }
    F0R(i, N+1) {
        cout << dp[i] << " \n"[i == N];
    }
}
