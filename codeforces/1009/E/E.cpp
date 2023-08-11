#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
const int M = 998244353;
int n, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    ll ans = 0;
    ll mult = 1, diff = 1;
    for (int i = n; i >= 1; --i) {
        ans = (ans + (A[i] * mult)%M)%M;
        mult = (mult * 2 + diff) % M;
        diff = (diff*2) % M;
    }
    cout << ans << '\n';


    return 0;
}
	

