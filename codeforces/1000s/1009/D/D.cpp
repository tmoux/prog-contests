#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int phi[maxn];

int getphi(int i) {
    int res = i;
    for (int p = 2; p*p <= i; p++) {
        if (i % p == 0) {
            while (i % p == 0) {
                i /= p;
            }
            res -= res/p;
        }
    }
    if (i > 1) {
        res -= res / i;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    phi[1] = 1;
    ll maxx = 0;
    for (int i = 2; i <= n; i++) {
        phi[i] = getphi(i);
        maxx += phi[i];
    }
    //check if valid
    if (m < n - 1 || m > maxx) {
        cout << "Impossible\n";
        return 0;
    }
    cout << "Possible\n";
    for (int i = 1; i <= n && m > 0; i++) {
        for (int j = i + 1; j <= n && m > 0; j++) {
            if (__gcd(i,j) == 1) {
                cout << i << ' ' << j << '\n';
                m--;
            }
        }
    }


    return 0;
}
	

