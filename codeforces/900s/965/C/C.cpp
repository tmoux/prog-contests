#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k, M, D;

ll f(ll x) {
    return x*(n/(k*x) + (n%(k*x))/(k*x));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> M >> D;
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << f(i) << '\n';
    }

    return 0;
}

