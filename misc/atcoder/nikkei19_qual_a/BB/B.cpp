#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;
    int ans = 0;
    for (int i = 0; i < n; i++) {
    	if (a[i] == b[i] && b[i] == c[i]) continue;
    	else if (a[i] == b[i] || b[i] == c[i] || a[i] == c[i]) {
    		ans++;
    	}
    	else ans += 2;
    }
    cout << ans << '\n';


    return 0;
}