#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int ans = 1;
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
    	int a, b; cin >> a >> b;
        ans += max(0,min(a,b)-max(x,y)+1);
        if (x == y) ans--;
        //cout << ans << endl;
        x = a, y = b;
    }
    cout << ans << '\n';

    return 0;
}
