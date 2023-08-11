#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    ll maxx = (ll)(n)*(n-1)/2;
    ll minx;
    if (n % 2 == 0) {
        minx = (ll)(n/2)*(n/2-1)+n/2;
    }
    else {
        minx = (ll)(n/2)*(n/2+1);
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ll xi, di; cin >> xi >> di;
        ans += xi * n;
        if (di >= 0) {
            ans += di * maxx;
        }
        else {
            ans += di * minx;
        }
    }
    cout << fixed << setprecision(10) << (double)(ans)/n << '\n';

    return 0;
}
	

