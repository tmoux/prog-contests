#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//ok im actually dumb

const int M = 1e9+7;
const int maxn = 6;
ll n;

ll modexp(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) {
            res = (res*a)%M;
        }
        a = (1LL*a*a)%M;
        b >>= 1;
    }
    return res;
}

struct Matrix
{
    ll m[maxn][maxn];
    int n;
    Matrix(int N_) {
        n = N_;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i][j] = 0;
            }
        }
    }
};

void madd(ll& a, ll b) {
    a = (a + b) % M;
}

Matrix operator*(Matrix a, Matrix b) {
    int n = a.n;
    Matrix res(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res.m[i][j] = (res.m[i][j] + (a.m[i][k]*b.m[k][j])%(M-1)) % (M-1);
            }
        }
    }
    return res;
}

Matrix power(Matrix a, ll p) {
    int n = a.n;
    Matrix ans(a.n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans.m[i][j] = (i==j);
        }
    }
    while (p) {
        if (p & 1) ans = ans * a;
        a = a * a;
        p >>= 1;
    }
    return ans;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    /*
    vector<ll> dp(20);
    for (int i = 4; i < 20; i++) {
        dp[i] = 2*i-6 + dp[i-1] + dp[i-2] + dp[i-3];
        cout << i << ": " << dp[i] << '\n';
    }
    */
    ll n, c, f[4];
    cin >> n >> f[1] >> f[2] >> f[3] >> c;
    Matrix tran(3);
    tran.m[0][0] = tran.m[0][1] = tran.m[0][2]
        = tran.m[1][0] = tran.m[2][1] = 1;
    tran = power(tran,n-3);
    ll p[4];
    for (int i = 0; i < 3; i++) {
        p[3-i] = tran.m[0][i];
    }
    
    Matrix t(5);
    t.m[1][0] = t.m[2][1] = t.m[3][2] = t.m[4][4] = 1;
    t.m[0][0] = t.m[0][4] = 2;
    t.m[0][3] = M-2;
    t = power(t,n-3);
    ll cp = t.m[0][4];
    /*
    Matrix t(5);
    t.m[0][0] = t.m[0][1] = t.m[0][2] = 1;
    t.m[1][0] = t.m[2][1] = 1;
    t.m[0][3] = 2;
    t.m[3][3] = t.m[3][4] = t.m[4][4] = 1;
    t = power(t,n);
    ll cp = t.m[1][4];
    */
    ll ans = modexp(c,cp);
    //cout << ans << '\n';
    for (int i = 1; i <= 3; i++) {
        ans = (ans*modexp(f[i],p[i]))%M;
        //cout << (i-1) << ": " << p[i] << '\n';
        //cout << ans << '\n';
    }
    //cout << "c: " << cp << '\n';
    cout << ans << '\n';
    /*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << t.m[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    /*
    for (int i = 0; i < 3; i++) {
        cout << tran.m[0][i] << ' ';
    }
    cout << '\n';
    */
}

