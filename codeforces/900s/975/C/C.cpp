#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read input
    int n, q; cin >> n >> q;
    vector<ll> pfx(n);
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        pfx[i] = (i == 0) ? ai : pfx[i-1] + ai;
    }
    //process queries. We keep counter currHealth, which is "total" damage
    //dealt to the soldiers and binary search for the smallest index
    //greater than it. If currHealth ever gets larger than the sum of all healths,
    //reset it to 0.
    ll currHealth = 0;
    for (int i = 0; i < q; i++) {
        ll qi; cin >> qi;
        currHealth += qi;
        if (currHealth >= pfx[n-1]) currHealth = 0;
        auto it = upper_bound(pfx.begin(),pfx.end(),currHealth);
        cout << (pfx.end()-it) << '\n';
    }
    return 0;
}
	

