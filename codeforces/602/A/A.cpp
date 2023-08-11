#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

ll compute(vector<ll>& d, int b) {
    ll ans = 0;
    ll mult = 1;
    for (int i = d.size() - 1; i >= 0; i--) {
        ans += d[i]*mult;
        mult *= b;
    }
    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, b; cin >> n >> b;
    vector<ll> d;
    for (int i = 0; i < n; i++) {
         ll x; cin >> x;
         d.push_back(x);
    }
    ll d1 = compute(d,b);
    cin >> n >> b;
    vector<ll> de;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        de.push_back(x);
    }
    ll d2 = compute(de,b);
    if (d1 < d2) {
        cout << "<\n";
    }
    else if (d1 > d2) {
        cout << ">\n";
    }
    else {
        cout << "=\n";
    }


    return 0;
}
	

