#include <iostream>
using namespace std;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    int ans = 0;
    for (int i = 1; i <= n; i++) if (x % i == 0 && x/i <= n) ans++;
    cout << ans << '\n';
    return 0;
}
	

