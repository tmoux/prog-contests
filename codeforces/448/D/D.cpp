#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m;
ll k;

bool check(ll x) { //possible if ord(x) >= k
    ll total = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        //i = row
        total += min(1LL*m,x/i);
        if (x % i == 0) cnt++;
    }
    return total >= k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    ll lo = 0, hi = 1LL*n*m+1;
    while (lo + 1 < hi) {
        ll m = (lo+hi)>>1;
        if (check(m)) hi = m;
        else lo = m;
    }
    cout << hi << '\n';


    return 0;
}

