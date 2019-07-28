#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 1e5+5;
int a[maxn];
int n;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int madd(int& a, int b) {
    a = (a+b) % M;
}

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res =  mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int len = 0;
    int cp = a[1];
    while (cp) {
        cp /= 10;
        len++;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int d = 0;
        while (a[i]) {
            int digit = a[i] % 10;
            madd(ans,mult(n,mult(modexp(10,d),digit)));
            madd(ans,mult(n,mult(modexp(10,d+1),digit)));
            d += 2;
            a[i] /= 10;
        }
    }
    cout << ans << '\n';
}

