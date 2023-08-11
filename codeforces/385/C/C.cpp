#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
const int maxx = 10000007;
int n, m, X[maxn];
ll cnt[maxx], pre[maxx], f[maxx];
bool composite[maxx];

ll query(int l, int r) {
    r = min(r,maxx-1);
    l = min(l,maxx-1);
    return pre[r] - pre[l-1];
}

void sieve() {
    for (int i = 2; i < maxx; i++) {
        if (!composite[i]) {
            for (int j = i; j < maxx; j+=i) {
                f[i] += cnt[j];
                if (j != i) composite[j] = true;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> X[i];
        cnt[X[i]]++;
    }
    sieve();
    for (int i = 2; i < maxx; i++) {
        pre[i] = pre[i-1] + f[i];
        //cout << i << ' ' << pre[i] << '\n';
    }
    int m; cin >> m;
    while (m--) {
        int l, r; cin >> l >> r;
        cout << query(l,r) << '\n';
    }
   
    return 0;
}
	

