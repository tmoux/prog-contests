#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int p; cin >> p;
    int ans = 0;
    for (int i = 1; i < p; i++) {
        int x = i;
        bool flag = true;
        for (int j = 1; j <= p-2; j++) {
            if ((x - 1) % p == 0) {
                flag = false;
                break;
            }
            x = (x*i) % p;
        }
        if (flag && (x-1) % p == 0) {
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}
	

