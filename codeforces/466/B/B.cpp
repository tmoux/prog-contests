#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, a, b; cin >> n >> a >> b;
    if (a * b >= n * 6) {
        cout << a*b << '\n';
        cout << a << ' ' << b << '\n';
        return 0;
    }
    ll minarea = 2e18, newa, newb;
    bool swapped = false;
    if (a > b) {
        swapped = true;
        swap(a,b);
    }
    for (ll aa = a; aa <= ceil(sqrt(6*n)); aa++) {
        ll bb = max((ll)(ceil(6*n/(double)(aa))),b);
        if (aa * bb < minarea) {
            minarea = aa*bb;
            newa = aa;
            newb = bb;
        }
    }

    cout << minarea << '\n';
    if (swapped) swap(newa,newb);
    cout << newa << ' ' << newb << '\n';

    return 0;
}
	

