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
const int MX = 100011; //check the limits, dummy

const int M = 60;
int N, K;
ld trans[MX][M*2];
ld dp[MX];
int num[MX];

void go(ld cost) {
    F0R(i, MX) dp[i] = 0;
    F0R(i, MX) num[i] = 0;
    F0R(i, N) {
        F0R(j, M*2) {
            if (i+j < N && ckmax(dp[i+j+1], dp[i] + trans[i][j] - cost)) {
                num[i+j+1] = num[i] + 1;
            }
        }
    }
}

void solve() {
    cin >> N >> K;
    int P[N], D[N];
    F0R(i, N) {
        cin >> P[i] >> D[i];
    }

    const int NP = 8000011;
    ld pows[NP];
    pows[0] = 1;
    FOR(i, 1, NP) pows[i] = pows[i-1] * 0.5;
    /*F0R(i, N) {
        lef[i][0] = 0;
        FOR(j, 1, M) {
            int p = i-j+1;
            lef[i][j] = lef[i][j-1];
            if (p >= 0) {
                lef[i][j] += P[p] * pows[D[i] - D[p]];
            }
        }
        rig[i][0] = 0;
        FOR(j, 1, M) {
            int p = i+j-1;

        }
    }*/
    F0R(i, N) {
        ld lef = 0;
        F0R(a, M) {
            if (i+a == N) break;
            if (a > 0) {
                lef *= pows[D[i+a]-D[i+a-1]];
            }
            lef += P[i+a];
            ld rig = 0;
            ckmax(trans[i][a], lef);
            FOR(b, 1, M) {
                if (i+a+b == N) break;
                rig += P[i+a+b] * pows[D[i+a+b]-D[i+a]];
                ckmax(trans[i][a+b], lef+rig);
            }
        }
    }

    ld hi = 1000, lo = 0;
    F0R(iter, 60) {
        ld mid = (lo+hi)/2;
        go(mid);
        //cout << mid << " " << num[N] << " TEST" << nl;
        if (num[N] == K) {
            lo = mid; hi = mid;
            break;
        } else if (num[N] < K)  {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    go(lo);
    cout << setprecision(20) << dp[N] + K * lo << nl;
    /*F0R(i, N) {
        cout << dp[i] << " " << num[i] << nl;
    }*/
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

