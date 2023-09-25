#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace superIO {
    int BUF=100000;
    int buf_readed = 0;
    int buf_index = 0;
    char buffer[100000];
    /*****************************************/
    char my_getchar(){
        char x;
        if(buf_index==buf_readed){
            buf_index=0;
            buf_readed=fread(buffer,1,BUF,stdin);
        }
        x=buffer[buf_index];
        buf_index++;
        return x;
    }
    /*************************************/

    //can return int or long long
    int getInt(){
        int r=0;
        char c;
        int sign=1;
        while(1){
            c=my_getchar();
            if(c=='-')
                sign=-1;

            if((c>='0' && c<='9')){
                r=(c-'0');
                break;
            }
        }
        while(1){
            c=my_getchar();
            if(!(c>='0' && c<='9'))
                break;
            r=r*10+(c-'0');
        }
        return sign*r;
    }
}
using namespace superIO;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
    template<class Fun>
    class y_combinator_result {
        Fun fun_;
        public:
            template<class T>
            explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

            template<class ...Args>
            decltype(auto) operator()(Args &&...args) {
                return fun_(std::ref(*this), std::forward<Args>(args)...);
            }
    };

    template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
        return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T_container,
         typename T = typename enable_if<!is_same<T_container, string>::value,
                                         typename T_container::value_type>::type>
ostream& operator<<(ostream &os, const T_container &v) {
    os << '['; string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

// combine should be associative and idempotent (e.g., min, max, gcd)
template<typename T, T (*combine)(T, T)>
struct SparseTable
{
    int n, maxk;
    vector<vector<T>> tb;
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    SparseTable() {}
    SparseTable(const vector<T>& a) : n(sz(a)) {
        maxk = 0;
        while (n >= (1<<maxk)) maxk++;
        tb.resize(maxk, vector<int>(n));
        for (int i = 0; i < n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 0; i < n; i++) {
                int nx = i + (1<<(k-1));
                if (nx < n) tb[k][i] = combine(tb[k-1][i], tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    T prod(int l, int r) {
        int g = lg(r-l+1);
        return combine(tb[g][l], tb[g][r-(1<<g)+1]);
    }
};

int mincomp(int x, int y) {
    return min(x, y);
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
    int n, maxk;
    bool is_0_index;
    vector<bool> isRed;
    vector<vector<pair<int, ll>>> adj;
    vector<int> udepth;
    vector<ll> depth, depthFromRed;
    vector<vector<int>> par;
    vector<int> E, Eindex;
    int e_idx = 0;
    SparseTable<int, mincomp> table;

    void dfs(int i, int p, int& t, ll nearestRedDepth) {
        Eindex[i] = e_idx;
        E[e_idx++] = i;
        depthFromRed[i] = depth[i] - nearestRedDepth;
        par[0][i] = p;
        for (int k = 1; k < maxk; k++) {
            par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
        }
        for (auto [j, w]: adj[i]) if (j != p) {
                udepth[j] = udepth[i] + 1;
                depth[j] = depth[i] + w;
                dfs(j, i, t, isRed[i] ? depth[i] : nearestRedDepth);
                E[e_idx++] = i;
            }
    }

    Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
        maxk = 0;
        while (n >= (1<<maxk)) maxk++;
        int sz = is_0_index ? n : n+1;
        isRed.resize(sz, false);
        adj.resize(sz);
        udepth.resize(sz, 0);
        depth.resize(sz, 0);
        depthFromRed.resize(sz, 0);
        par = vector<vector<int>>(maxk, vector<int>(sz, -1));
        E.resize(2*sz-1);
        Eindex.resize(sz, -1);
        e_idx = 0;
    }
    void add_edge(int u, int v, ll w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void init() {
        int root = is_0_index ? 0 : 1;
        int t = 0;
        dfs(root, -1, t, 0);
        table = SparseTable<int, mincomp>(E);
    }

    int lca(int a, int b) {
        // int i = Eindex[a], j = Eindex[b];
        // if (i > j) swap(i, j);
        // return table.prod(i, j);
        if (udepth[a] > udepth[b]) swap(a, b);
        for (int k = maxk-1; k >= 0; k--) {
            int bb = par[k][b];
            if (bb != -1 && udepth[bb] >= udepth[a]) b = bb;
        }
        if (a == b) return a;
        for (int k = maxk-1; k >= 0; k--) {
            int aa = par[k][a];
            int bb = par[k][b];
            if (aa != bb) {
                a = aa;
                b = bb;
            }
        }
        return par[0][a];
    }

    int lca2(int a, int b) {
        int i = Eindex[a], j = Eindex[b];
        if (i > j) swap(i, j);
        return table.prod(i, j);
    }
};

void solve() {
    int N = getInt(), M = getInt(), Q = getInt();
    // int N, M, Q; cin >> N >> M >> Q;
    Tree tree(N);
    F0R(i, M) {
        int x = getInt(); x--;
        // int x; cin >> x; x--;
        tree.isRed[x] = 1;
    }
    REP(N-1) {
        int u = getInt(), v = getInt(), w = getInt();
        // int u, v, w; cin >> u >> v >> w;
        u--, v--;
        tree.add_edge(u, v, w);
    }
    tree.init();

    vector<pair<ll, int>> ks(N);
    auto query = [&](int sz) -> ll {
        if (sz == 0) return 0;
        ll ans = ks.front().first;
        int lc = ks.front().second;
        ll curd = 0;
        F0R(idx, sz) {
            auto [d, i] = ks[idx];
            // assert(tree.lca(lc, i) == tree.lca2(lc, i));
            int lcN = tree.lca(lc, i);
            curd = max(curd + tree.depth[lc] - tree.depth[lcN],
                       tree.depth[i] - tree.depth[lcN]);
            ll tr = max(curd, idx + 1 < sz ? ks[idx+1].first : 0);
            // cout << ks[idx] << ": " << tr << endl;
            ckmin(ans, tr);

            lc = lcN;
            // DEBUG(lc);
        }
        return ans;
    };

    // cout << tree.depthFromRed << endl;
    ll ts = 0;
    REP(Q) {
        int k = getInt();
        // int k; cin >> k;
        ts += k;
        int c = 0;
        REP(k) {
            int x = getInt(); x--;
            // int x; cin >> x; x--;
            if (!tree.isRed[x])
                ks[c++] = {tree.depthFromRed[x], x};
        }
        sort(ks.begin(), ks.begin() + c, greater());
        cout << query(c) << '\n';
    }
    // DEBUG(ts);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = getInt();
    // int T; cin >> T;
    while (T--) solve();
}
