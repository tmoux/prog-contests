#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    while (t--) {
    	int n; cin >> n;
    	cout << (n % 2 == 0 ? 1 : 0) << '\n';
    }

    return 0;
}