#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
ll n, A, B;
ll sz[maxn];
ll S = 0;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.in","r",stdin);
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) {
        cin >> sz[i];
        S += sz[i];
    }
    sort(sz+2,sz+n+1);
    int idx = n;
    int ans = 0;
    while (sz[1]*A < S*B) {
        S -= sz[idx];
        idx--;
        ans++;
    }
    cout << ans << '\n';

    return 0;
}
	

