#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> n >> k;
    if (k <= n/2+n%2) {
        cout << 2*k-1 << '\n';
    }
    else {
        k -= (n/2 + n%2);
        cout << (2*k) << '\n';
    }


    return 0;
}
	

