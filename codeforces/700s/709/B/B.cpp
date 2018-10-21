#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
ll A[maxn];

ll mindist(ll i, ll minn, ll maxx) {
    ll a1 = min(abs(i-minn) + (maxx - minn), abs(maxx-i) + (maxx-minn));
    return a1;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll a; cin >> a;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    if (n == 2) {
        cout << min(abs(a-A[0]),abs(a-A[1])) << '\n';
        return 0;
    }
    ll ans = min(mindist(a,A[0],A[n-2]),mindist(a,A[1],A[n-1]));
    cout << ans << '\n';


    return 0;
}
	

