#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int maxk = 62;
ll f(ll l, ll r, int k) {
    if (k < 0) return 0LL;
    if (!(l & (1LL << k) ^ r & (1LL << k))) return f(l,r,k-1);
    return (1LL << (k+1)) - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll l, r; cin >> l >> r;
    cout << f(l,r,maxk) << '\n';
    return 0;
}
	

