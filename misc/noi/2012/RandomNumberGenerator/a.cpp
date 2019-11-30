#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

ll m, a, c, x_0, n, g;

void madd(ll& a, ll b) {
    a += b;
    if (a >= m) a -= m;
}

long long mult(long long a, long long b) 
{ 
    long long res = 0; // Initialize result 
  
    // Update a if it is more than 
    // or equal to mod 
    a %= m; 
  
    while (b) 
    { 
        // If b is odd, add a with result 
        if (b & 1) 
            res = (res+a) % m;
  
        // Here we assume that doing 2*a 
        // doesn't cause overflow 
        a = (a+a) % m;
  
        b >>= 1; // b = b / 2 
    } 
    return res;
}

struct Matrix
{
    ll a[2][2];
    Matrix() {
        a[0][0] = a[1][1] = 1;
        a[0][1] = a[1][0] = 0;
    }
    Matrix(int _a, int b, int c, int d) {
        a[0][0] = _a;
        a[0][1] = b;
        a[1][0] = c;
        a[1][1] = d;
    }
    Matrix operator*(Matrix b) {
        Matrix ret(0,0,0,0);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    madd(ret.a[i][j],mult(a[i][k],b.a[k][j]));
                }
            }
        }
        return ret;
    }
};

Matrix mpow(Matrix a, ll b) {
    Matrix res;
    while (b > 0) {
        if (b&1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m >> a >> c >> x_0 >> n >> g;
    Matrix t(a,c,0,1);
    t = mpow(t,n);
    ll ans = mult(t.a[0][0],x_0);
    madd(ans,t.a[0][1]);
    ans %= g;
    cout << ans << '\n';
}

