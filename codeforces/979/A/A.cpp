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
    ll n; cin >> n; n++;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    cout << (n % 2 == 0 ? n/2 : n) << '\n';

    return 0;
}
	

