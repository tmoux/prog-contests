#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

ll maxsearch = 100000LL;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, m; cin >> n >> m;
    int ans = 0;
    for (int i = 0; i <= maxsearch; i++) {
        if (n - i*i >= 0 && i * (1 + i*i*i - 2*n*i) == m - n*n) {
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}
	

