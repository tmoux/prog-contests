#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex <ld> cd;

typedef pair<int, int> pi;
typedef pair <ll, ll> pl;
typedef pair <ld, ld> pd;

typedef vector<int> vi;
typedef vector <ld> vd;
typedef vector <ll> vl;
typedef vector <pi> vpi;
typedef vector <pl> vpl;
typedef vector <cd> vcd;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'

template<typename T>
ostream &operator<<(ostream &o, const vector <T> &v) {
    o << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        o << *it;
        if (next(it) != v.end()) o << ", ";
    }
    o << "]";
    return o;
}

const int maxn = 55;
int N, K;
int a[maxn];
ll dp[maxn][maxn][maxn][maxn]; //(index, # chosen, 2nd biggest, 1st biggest so far)

ll f(int i, int j, int k1, int k2) {
    ll& res = dp[i][j][k1][k2];
    if (res != -1) return res;
    if (i == N) {
        return res = j == K ? 1LL : 0LL;
    }
    res = f(i+1, j, k1, k2);
    if (a[i] <= a[k1] + a[k2]) {
        res += f(i+1, j+1, k2, i);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    F0R(i, N) cin >> a[i];
    sort(a,a+N);
    memset(dp, -1, sizeof dp);
    ll ans = 0;
    for (int k1 = 0; k1 < N; k1++) {
        for (int k2 = k1+1; k2 < N; k2++) {
            ans += f(k2+1, 2, k1, k2);
        }
    }
    cout << ans << '\n';
}
