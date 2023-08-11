#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int pre[maxn];
int prod[maxn];
int n, M;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> M;
    for (int i = 1; i <= n; i++) {
        cin >> prod[i];
    }
    prod[0] = 0;
    prod[n+1] = M;
    bool on = true;
    for (int i = 1; i <= n+1; i++) {
        if (on) {
            on = !on;
            pre[i] = pre[i-1] + (prod[i]-prod[i-1]);
        }
        else {
            on = !on;
            pre[i] = pre[i-1];
        }
    }
    int ans = pre[n+1];
    for (int i = 1; i <= n; i += 2) {
        int p = prod[i] + 1;
        int newans = pre[i];
        int flip = (M-prod[i]) - (pre[n+1] - pre[i]) - 1;
        newans += flip;
        ans = max(newans,ans);
    }
    for (int i = 1; i <= n+1; i += 2) {
        int p = prod[i] - 1;
        int newans = pre[i-1] + (p-prod[i-1]);
        int flip = (M-prod[i]) - (pre[n+1] - pre[i]);
        newans += flip;
        ans = max(newans,ans);
    }
    cout << ans << '\n';


    return 0;
}
	

