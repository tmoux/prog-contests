#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
const int maxn = 1e5+5;
int n, k, a[maxn];

int fac[maxn], ifac[maxn];
int choose(int n, int r) {
    if (n < r) return 0;
    return mult(fac[n],mult(ifac[r],ifac[n-r]));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    fac[0] = 1;
    ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int add = mult(choose(i,k-1),a[i]);
        //cout << i << ": " << add << '\n';
        madd(mx,add);
    }
    int mn = 0;
    for (int i = 0; i < n; i++) {
        int add = mult(choose(n-i-1,k-1),a[i]);
        //cout << i << ": " << add << '\n';
        madd(mn,add);
    }
    //cout << "mx = " << mx << '\n';
    //cout << "mn = " << mn << '\n';
    cout << (mx-mn+M)%M << '\n';
}

