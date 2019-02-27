#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("in","r",stdin);
    int n; cin >> n;
    int ans = 0;
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
    	int a, b; cin >> a >> b;
    	if (x == y) ans++;
    	ans += min(a,b) - x;
    	if (x == y) ans--;
    	x = a;
    	y = b;
    	cout << ans << '\n';
    }
    cout << ans << '\n';


    return 0;
}