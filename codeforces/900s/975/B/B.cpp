#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 14;
ll manc[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < maxn; i++) {
        cin >> manc[i];
    }

    ll ans = 0;
    for (int i = 0; i < maxn; i++) {
        ll cp[maxn];
        for (int j = 0; j < maxn; j++) {
            cp[j] = manc[j];
        }
        cp[i] = 0;
        for (int j = 0; j < maxn; j++) {
            cp[j] += manc[i]/maxn;
        }
        for (int j = 0; j < (manc[i]%maxn); j++) {
            cp[(i+j+1)%maxn]++;
        }
        ll tr = 0;
        for (int j = 0; j < maxn; j++) {
            if (cp[j] % 2 == 0) {
                tr += cp[j];
            }
        }
        ans = max(ans,tr);
    }
    
    cout << ans << '\n';

    return 0;
}
	

