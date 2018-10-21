#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 300005;
int n;
ll x, y;
string s;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x >> y >> s;
    int numZeros = 0;
    char curr = '1';
    for (char c: s) {
        if (curr == '1' && c == '0') {
            numZeros++;
        }
        curr = c;
    }

    if (numZeros == 0) {
        cout << 0 << '\n';
        return 0;
    }

    ll minans = -1;
    for (ll i = 0; i <= numZeros - 1; i++) {
        ll j = numZeros - i;
        if (minans == -1 || i*x + j*y < minans) {
            minans = i*x + j*y;
        }
    }
    cout << minans << '\n';


    return 0;
}
	

