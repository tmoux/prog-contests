#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_set>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, k;
ll ips[maxn];

ll fmt(int a[4]) {
    return ((a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3]);
}

string outfmt(ll a) {
    string res = "";
    for (int i = 3; i >= 0; i--) {
        int r = 0;
        for (int j = 0; j < 8; j++) {
            int b = ((a >> (i*8+j)) & 1) << j;
            r |= b;
        }
        res += to_string(r);
        if (i != 0) res += '.';
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d %d\n",&n,&k);
    for (int i = 0; i < n; i++) {
        int a[4];
        scanf("%d.%d.%d.%d\n",a,a+1,a+2,a+3);
        ll f = fmt(a);
        ips[i] = f;
    }

    ll subnetMask = 0LL;
    for (int i = 31; i > 0; i--) {
        subnetMask |= (1 << i);
        unordered_set<ll> addresses;
        for (int j = 0; j < n; j++) {
            addresses.insert(subnetMask & ips[j]);
        }
        if (addresses.size() == k) {
            cout << outfmt(subnetMask) << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';


    return 0;
}
	

