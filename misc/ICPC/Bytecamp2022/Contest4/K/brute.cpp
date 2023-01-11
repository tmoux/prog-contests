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

// An assignment has a winner iff there are no two adjacent defenders
// (i.e., the defenders form an independent set.)
// This is because if there are two adjacent defenders, if one player is losing,
// they can just defend back and forth so that the game never ends.
// Otherwise, the neighbors of a defender are all attackers.
// The outcome of each arrangement can be computed by calculating the grundy number of each individual defender and xoring them, since the total is a sum of independent games.
//
// So we just have to count the number of assignments with xor 0 and nonzero.
// It's easier to count the total number of assignments (that form independent sets), and the total number of ones with xor 0.
// The total number of independent sets can be computed with standard MITM and SoS DP techniques.
// It seems we can similarly compute the ones with xor 0: for each half-set S with xor X, find the sum of half-sets T also with xor X.
// This runs in 20 * 2^20, which should be fine.

int mex(vector<int> v) {
    sort(all(v)); v.erase(unique(all(v)), v.end());
    for (int i = 0; i < sz(v); i++) if (i != v[i]) return i;
    return sz(v);
}

int main() {
    int N; cin >> N;
    vector<int> T(N);
    for (auto& x: T) cin >> x;
    int M; cin >> M;
    vector<vector<int>> adj(N);
    REP(M) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto grundy = [&](int i) -> int {
        vector<int> G(T[i] + 1, 0);
        for (int x = 1; x <= T[i]; x++) {
            vector<int> v;
            for (int j: adj[i]) v.push_back(G[max(0, x - T[j])]);
            G[x] = mex(v);
        }
        return G[T[i]];
    };
    vector<int> G(N); F0R(i, N) G[i] = grundy(i);

    int A = 0, B = 0;
    F0R(mask, 1<<N) {
        bool poss = true;
        F0R(i, N) if (mask & (1<<i)) {
            for (int j: adj[i]) if (mask & (1<<j)) {
                    poss = false;
                }
        }
        if (poss) {
            int x = 0;
            F0R(i, N) if (mask & (1<<i)) x ^= G[i];

            (x ? A : B)++;
        }
    }

    cout << A << '\n' << B << '\n';
}
