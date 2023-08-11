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
int N, K;

vector<pair<int, int>> adj[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    F0R(i, N-1) {
        int a, b; cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    int ans = 0;
    F0R(mask, 1 << (N-1)) {
        vector<bool> b(N-1);
        F0R(i, N-1) {
            if (mask & (1 << i)) b[i] = 1;
        }
        vector<bool> vis(N+1);

        pair<int, int> best = {-1, -1};
        auto dfs = y_combinator([&](auto dfs, int i, int p, int d, bool v) -> void {
            ckmax(best, {d, i});
            if (v) vis[i] = 1;
            for (auto [j, id]: adj[i]) {
                if (j == p || b[id]) continue;
                dfs(j, i, d+1, v);
            }
        });
        // cout << "mask " << mask << endl;
        // cout << b << endl;
        bool poss = true;
        for (int i = 1; i <= N; i++) {
            if (!vis[i]) {
                best = {-1, -1};
                dfs(i, i, 0, false);
                auto [_, j] = best;
                best = {-1, -1};
                dfs(j, j, 0, true);
                auto [d, k] = best;
                if (d > K) {
                    poss = false;
                    // cout << "breaking " << i << ' ' << d << endl;
                    break;
                }
            }
        }
        // cout << poss << endl;
        if (poss) ans++;
    }
    cout << ans << '\n';
}
