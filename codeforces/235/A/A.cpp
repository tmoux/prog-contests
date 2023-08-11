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

    ll n; cin >> n;
    if (n == 1 || n == 2) {
        cout << n << '\n';
        return 0;
    }
    if (n == 3) {
        cout << 6 << '\n';
        return 0;
    }
    if (n % 2 == 0) {
        if (n % 3 == 0) {
            cout << ((n-1)*(n-2)*(n-3)) << '\n';
        }
        else {
            cout << (n*(n-1)*(n-3)) << '\n';
        }
    }
    else {
        cout << (n*(n-1)*(n-2)) << '\n';
    }


    return 0;
}
	

