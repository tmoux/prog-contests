#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        queue<int> q;
        int bed[205];
        for (int i = 1; i <= n; i++) {
            bed[i] = 999999;
        }
        for(int i = 0; i < k; i++) {
            int xi; cin >> xi;
            bed[xi] = 1;
            q.push(xi);
        }
        while (!q.empty()) {
            int f = q.front();
            int n1 = f-1, n2 = f+1;
            if (1 <= n1 && n1 <= n) {
                if (bed[f] + 1 < bed[n1]) {
                    bed[n1] = bed[f]+1;
                    q.push(n1);
                }
            }
            if (1 <= n2 && n2 <= n) {
                if (bed[f] + 1 < bed[n2]) {
                    bed[n2] = bed[f] + 1;
                    q.push(n2);
                }
            }
            q.pop();
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans,bed[i]);
        }
        cout << ans << '\n';
    }


    return 0;
}
	

