#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m, freq[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
    	int l, r; cin >> l >> r;
    	for (int i = l; i <= r; i++) {
    		freq[i]++;
    	}

    }
    for (int i = 1; i <= n; i++) {
    	if (freq[i] != 1) {
    		cout << i << ' ' << freq[i] << '\n';
    		return 0;
    	}
    }
    cout << "OK\n";

    return 0;
}