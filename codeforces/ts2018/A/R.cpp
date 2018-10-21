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
    ll x0 = 0, x1 = 4;
    ll x2 = 4*x1 - 3*x0;
    ll n = 2;
    while (x2 % 83 != 0) {
        //cout << x2 << '\n';
        x0 = x1;
        x1 = x2;
        x2 = 4*x1 - 3*x0;
        n++;
    }
    cout << x2 << '\n';
    cout << n << '\n';


    return 0;
}
	

