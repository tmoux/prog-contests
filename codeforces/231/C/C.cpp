#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const ll maxn = 100005;
ll n, K, A[maxn], pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> K;
    for (ll i = 1; i <= n; i++) {
        cin >> A[i];
    }
    sort(A+1,A+n+1);
    for (ll i = 1; i <= n; i++) {
        pre[i] = A[i] + pre[i-1];
    }

    ll maxOcc = 0, idx;
    for (ll i = 1; i <= n; i++) {
        //find maximum j such that (j * A[i]) - (pre[j]) <= k
        ll j = i;
        for (ll k = 17; k >= 0; k--) {
            ll newj = j - (1 << k);
            
            if (newj >= 1 && ((i-newj)*(long long)A[i]) - (pre[i-1] - pre[newj-1]) <= K) {
                j = newj;
            }
        }
        ll numOcc = i - j + 1;
        if (numOcc > maxOcc) {
            maxOcc = numOcc;
            idx = A[i];
        }
        //cout << A[i] << ' ' << A[j] << '\n';
    }

    cout << maxOcc << ' ' << idx << '\n';

    return 0;
}
	

