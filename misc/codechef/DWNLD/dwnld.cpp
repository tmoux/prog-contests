#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int ti, di; cin >> ti >> di;
            if (k == 0) {
                ans += ti*di;
            }
            else if (k - ti >= 0) {
                k -= ti;
            }
            else {
                int diff = abs(k - ti);
                k = 0;
                ans += diff*di;
            }
        }
        cout << ans << '\n';
    }


    return 0;
}
	

