#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair 
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 

template<class T> bool ckmin(T& a, const T& b) { 
    return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
    return a < b ? a = b, 1 : 0; } 
int pct(int x) { return __builtin_popcount(x); } 
int bit(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
int cdiv(int a, int b) { return a/b+!(a<0||a%b == 0); } // division of a by b rounded up, assumes b > 0 

// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);

template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }

template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

// TO_STRING
#define ts to_string
template<class A, class B> str ts(pair<A,B> p);
template<class A> str ts(complex<A> c) { return ts(mp(c.real(),c.imag())); }
str ts(bool b) { return b ? "true" : "false"; }
str ts(char c) { str s = ""; s += c; return s; }
str ts(str s) { return s; }
str ts(const char* s) { return (str)s; }
str ts(vector<bool> v) { 
    bool fst = 1; str res = "{";
    F0R(i,sz(v)) {
        if (!fst) res += ", ";
        fst = 0; res += ts(v[i]);
    }
    res += "}"; return res;
}
template<size_t SZ> str ts(bitset<SZ> b) {
    str res = ""; F0R(i,SZ) res += char('0'+b[i]);
    return res; }
template<class T> str ts(T v) {
    bool fst = 1; str res = "{";
    for (const auto& x: v) {
        if (!fst) res += ", ";
        fst = 0; res += ts(x);
    }
    res += "}"; return res;
}
template<class A, class B> str ts(pair<A,B> p) {
    return "("+ts(p.f)+", "+ts(p.s)+")"; }

// OUTPUT
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { 
    pr(h); pr(t...); }
void ps() { pr("\n"); } // print w/ spaces
template<class H, class... T> void ps(const H& h, const T&... t) { 
    pr(h); if (sizeof...(t)) pr(" "); ps(t...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
    cerr << to_string(h); if (sizeof...(t)) cerr << ", ";
    DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

// FILE I/O
void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(string s = "") {
    unsyncIO();
    // cin.exceptions(cin.failbit); 
    // throws exception when do smth illegal
    // ex. try to read letter into int
    if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

template<int SZ> struct TopoSort {
    int N, in[SZ];
    vi res, adj[SZ];
    void ae(int x, int y) { adj[x].pb(y), in[y] ++; }
    bool sort(int NN) {
        N = NN; queue<int> todo;
        F0R(i,N) if (!in[i]) todo.push(i);
        while (sz(todo)) {
            int x = todo.front(); todo.pop(); res.pb(x);
            trav(i,adj[x]) if (!(--in[i])) todo.push(i);
        }
        return sz(res) == N;
    }
};

TopoSort<500> T;
int n,m;
bool link[500][500];
vi out[500];

/**
 * Description: Fast flow. After computing flow, edges $$${u,v}$$$ such that 
    * $$$level[u] \neq -1,$$$ $$$level[v] = -1$$$ are part of min cut.
 * Time: $$$O(N^2M)$$$ flow, $$$O(M\sqrt N)$$$ bipartite matching
 * Source: GeeksForGeeks, Chilli
 * Verification: RMI 2017 Day 1 Fashion
    * https://pastebin.com/VJxTvEg1
 */

template<int SZ> struct Dinic {
    typedef ll F; // flow type
    struct Edge { int to, rev; F flow, cap; };
    int N,s,t;
    vector<Edge> adj[SZ];
    typename vector<Edge>::iterator cur[SZ];
    void ae(int u, int v, F cap) {
        assert(cap >= 0); // don't try smth dumb
        Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, 0};
        adj[u].pb(a), adj[v].pb(b);
    }
    int level[SZ];
    bool bfs() { // level = shortest distance from source
        F0R(i,N) level[i] = -1, cur[i] = begin(adj[i]);
        queue<int> q({s}); level[s] = 0; 
        while (sz(q)) {
            int u = q.ft; q.pop();
            trav(e,adj[u]) if (level[e.to] < 0 && e.flow < e.cap) 
                q.push(e.to), level[e.to] = level[u]+1;
        }
        return level[t] >= 0;
    }
    F sendFlow(int v, F flow) {
        if (v == t) return flow;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& e = *cur[v];
            if (level[e.to]!=level[v]+1||e.flow==e.cap) continue;
            auto df = sendFlow(e.to,min(flow,e.cap-e.flow));
            if (df) { // saturated at least one edge
                e.flow += df; adj[e.to][e.rev].flow -= df;
                return df;
            }
        }
        return 0;
    }
    F maxFlow(int NN, int _s, int _t) {
        N = NN, s = _s, t = _t; if (s == t) return -1;
        F tot = 0;
        while (bfs()) while (auto df = sendFlow(s,
            numeric_limits<F>::max())) tot += df;
        return tot;
    }
};

Dinic<1005> D;

int main() {
    setIO(); re(n,m);
    F0R(i,m) {
        int x,y; re(x,y);
        T.ae(x,y);
        link[x][y] = 1;
        //dbg("HUH",x,y);
    }
    F0R(k,n) F0R(a,n) F0R(b,n) link[a][b] |= link[a][k]&link[k][b];
    F0R(i,n) F0R(j,n) if (link[i][j]) {
        //cout << i << ' ' << j << '\n';
    }
    T.sort(n);
    vi bad; F0R(i,n) if (T.in[i]) bad.pb(i);
    //dbg(bad,T.res);
    trav(a,bad) F0R(i,n) link[a][i] = link[i][a] = 0;
    F0R(i,n) {
        D.ae(2*n,i,1);
        D.ae(i+n,2*n+1,1);
    }
    F0R(i,n) F0R(j,n) dbg(i,j,link[i][j]);
    F0R(i,n) F0R(j,n) if (link[i][j]) {
        //cout << i << ' ' << j << '\n';
        D.ae(i,n+j,1);
    }
    int chain = n-sz(bad)-D.maxFlow(2*n+2,2*n,2*n+1);
    ps(chain);
}
