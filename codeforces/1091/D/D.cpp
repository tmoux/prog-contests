#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 998244353;
const int maxn = 1e6+6;
int n;

ll fac[maxn];
ll f[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    fac[0] = 1;
    f[1] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (fac[i-1] * i) % M;  
    for (int i = 2; i <= n; i++) {
        f[i] = ((f[i-1] + fac[i-1] - 1) * i) % M;
    }
    cout << f[n] << '\n';

    return 0;
}

