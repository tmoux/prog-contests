#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
 
#include <bits/stdc++.h>
 
using namespace std;
 
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
const int MX = 4000; //check the limits, dummy


vi get(int K) {
    vi res;
    string S; cin >> S;
    F0R(i, K) {
        char C = S[i];
        int X = C - '0';
        if ('a' <= C && C <= 'f') {
            X = 10 + C - 'a';
        }
        F0Rd(j, 4) {
            if (X & (1 << j)) {
                res.pb(1);
            } else res.pb(0);
        }
    }
    return res;
}

void solve() {

    int N; cin >> N;
    int M; cin >> M;
    int K; cin >> K;
    vector<vi> B;
    vector<vi> A;
    F0R(i, N) B.pb(get(K));
    F0R(i, M) A.pb(get(K));
    K *= 4;
    bool zer[M]; F0R(i, M) zer[i] = true;
    F0R(i, M) F0R(j, K) if (A[i][j] != 0) zer[i] = false;
    vector<vi> basis;
    vi rep;
    set<int> rem;
    F0R(i, K) rem.ins(i);
    int ans[M]; F0R(i, M) ans[i] = -1;
    bool foundOut = false;
    F0R(i, N) {
        int inB = -1;
        F0R(j, sz(basis)) {
            if (B[i][rep[j]] == 0) {
                continue;
            }
            F0R(k, K) {
                B[i][k] ^= basis[j][k];
            }
        }

        trav(a, rem) {
            if (B[i][a] == 0) continue;
            inB = a;
            basis.pb(B[i]);
            rep.pb(a);
            rem.erase(a);
            break;
        }
        if (inB == -1) {
            if (!foundOut) {
                F0R(j, M) {
                    if (zer[j]) ans[j] = i+1;
                }
            }
            foundOut = true;
            continue;
        }

        F0R(j, M) {
            if (ans[j] != -1) continue;
            if (A[j][inB] == 0) {
                continue;
            }
            bool found = false;
            F0R(k, K) {
                A[j][k] ^= B[i][k];
                if (A[j][k]) found = true;
            }
            if (!found) {
                ans[j] = i+1;
            }
        }
    }
    F0R(i, M) {
        cout << ans[i] << nl;
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


