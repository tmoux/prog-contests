#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll check(ll x) {
	ll res = 0;
	ll div = 5;
	while (x/div > 0) {
		res += x/div;
		div *= 5;
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    ll Q;
    while (cin >> Q) {
	    ll lo = 0, hi = 1e18+5;
	    while (lo + 1 < hi) {
	    	ll mid = (lo+hi)/2;
	    	ll n = check(mid);
	    	if (n < Q) {
	    		lo = mid;
	    	}
	    	else hi = mid;
	    }
	    if (check(hi) == Q) {
	    	cout << hi << '\n';
	    }
	    else cout << "No solution\n";
	}


    return 0;
}