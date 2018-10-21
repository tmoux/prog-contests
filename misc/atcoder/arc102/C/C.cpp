#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    ll res = 0LL;
    ll zeros = n / k;
    res += 1LL*zeros*zeros*zeros;
    if (k % 2 == 0) {
        int half = (n + k/2)/k;
        res += 1LL*half*half*half;
    }
    cout << res << '\n';

    return 0;
}
	

