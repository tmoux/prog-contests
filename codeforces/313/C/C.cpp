#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

ll n, N;
ll A[2000005], pre[2000005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    ll ans = 0;
    sort(A+1,A+n+1,greater<ll>());
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + A[i];
    }
    ll c = 1;
    while (true) {
        ans += pre[c];
        if (c == n) break;
        c *= 4;
    }
    cout << ans << '\n';


    return 0;
}
	

