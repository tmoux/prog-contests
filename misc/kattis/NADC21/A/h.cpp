#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>;
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1000000007;
const char nl = '\n';
const int MX = 100001; //check the limits, dummy
ll base1[MX], base2[MX];
int base;
ll b1Inv, b2Inv;
ll baseExp(ll power, ll prime) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = baseExp(power / 2, prime); cur = cur * cur; cur = cur % prime;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % prime;
            return cur;
        }
    }
struct hsh  {
    ll p1, p2;
    ll val1, val2;
    vl val1s, val2s;
    vl nums;
    hsh() {
        p1 = 1000000007;
        p2 = 1000000009;
        val1 = 0;
        val2 = 0;
        val1s.pb(0); val2s.pb(0);
    }
    hsh(string S) {
        p1 = 1000000007;
        p2 = 1000000009;
        val1 = 0;
        val2 = 0;
        val1s.pb(0); val2s.pb(0);
        F0R(i, sz(S)) {
            push_back(S[i] - 'a');
        }
    }
    void push_back(ll v) {
        val1 *= base;
        val1 += v;
        val1 %= p1;
        val2 *= base;
        val2 += v;
        val2 %= p2;
		val1s.pb(val1);
		val2s.pb(val2);
        nums.pb(v);
    }
    void pop_back() {
        //warning: the extent to which this has been tested is limited lol
        ll v = nums[sz(nums)-1]; nums.pop_back();
        val1s.pop_back(); val2s.pop_back();
        val1 += p1 - v; val1 *= b1Inv;
        val1 %= p1;
        val2 += p2 - v; val2 *= b2Inv; val2 %= p2;
    }
    ll get(int L, int R) {
        ll A = (val1s[R+1] - (val1s[L] * base1[R-L+1]) % p1 + p1) % p1;
        ll B = (val2s[R+1] - (val2s[L] * base2[R-L+1]) % p2 + p2) % p2;
        return A * p2 + B;
    }
};
void prepHash() {
    base = uniform_int_distribution<int>(1000, MOD-2)(rng);
    base1[0] = 1; base2[0] = 1;
    b1Inv = baseExp(1000000005, 1000000007);
    b2Inv = baseExp(1000000007, 1000000009);
    FOR(i, 1, MX) {
        base1[i] = (base1[i-1] * base) % 1000000007;
        base2[i] = (base2[i-1] * base) % 1000000009;
    }
}
void solve() {
    string S;  //cin >> S;
    F0R(i, 200000) S += 'a' + uid(0, 25);
    int N = sz(S);
    prepHash();
    hsh H(S);
    set<int> lens;
    vector<pair<string, int>> qs;
    map<ll, int> M;
    /*int Q; cin >> Q;
    F0R(i, Q) {
        string A; int K; cin >> A >> K;
        qs.pb({A, K});
        lens.ins({sz(A)});
    }*/
    int tot = 0;
    int nxtVal = 1;
    while (tot < 200000) {
        string cur; F0R(i, nxtVal) cur += 'a' + uid(0, 25);
        qs.pb({cur, 1});
        lens.ins(nxtVal);
        tot += nxtVal;
        nxtVal++;
    }
    int Q = sz(qs);
    vector<vi> pos;
    trav(a, qs) {
        hsh X(a.f);
        if (!M.count(X.get(0, sz(a.f)-1))) {
            M.ins({X.get(0, sz(a.f)-1), sz(pos)});
            pos.pb(vi());
        }
    }
    trav(l, lens) {
        F0R(i, sz(S) - l + 1) {
            ll X = H.get(i, i+l-1);
            if (M.count(X)) {
                pos[M[X]].pb(i);
            }
        }
    }
    F0R(i, Q) {
        string A; int K; A = qs[i].f; K = qs[i].s;
        hsh h(A);
        ll V = h.get(0, sz(A) - 1);
        if (M.find(V) == M.end()) {
            cout << -1 << nl;
        } else {
            int p = M[V];
            if (sz(pos[p]) < K) {
                cout << -1 << nl;
            } else {
                cout << pos[p][K-1]+1 << nl;
            }
        }
    }
}
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
//    cin >> T;
    while(T--) {
        solve();
    }
	return 0;
}
// read the question correctly (ll vs int)
// template by bqi343
