#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ceil(ll a, ll b) {
    return a%b == 0 ? a/b : a/b+1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> n >> k;
    ll red = ceil(2*n,k);
    ll green = ceil(5*n,k);
    ll blue = ceil(8*n,k);
    cout << (red+green+blue) << '\n';


    return 0;
}

