#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> n >> k;
    ll s, e;
    if (k - n > 0) {
        e = n;
        s = k - n;
    }
    else {
        s = 1;
        e = k - 1;
    }
    ll space = (e - s + 1) / 2;
    space = max(0LL,space);
    cout << space << '\n';
    
    return 0;
}
	

