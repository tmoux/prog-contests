#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
ll n, A[maxn];

ll ceil(ll a, ll b) {
    return (a % b == 0 ? a/b : a/b+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll maxa = 0;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        maxa = max(maxa,A[i]);
        sum += A[i];
    }

    ll a1 = ceil(sum,n-1);
    ll ans = max(a1,maxa);
    cout << ans << '\n';

     

    return 0;
}
	

