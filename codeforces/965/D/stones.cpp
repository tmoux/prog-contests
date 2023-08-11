#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int w, l, A[maxn], pfx[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> w >> l;
    for (int i = 1; i <= w-1; i++) {
        cin >> A[i];
        pfx[i] = pfx[i-1] + A[i];
    }
    int ans = 2e9;
    for (int i = l; i < w; i++) {
        int tr = pfx[i] - pfx[i-l];
        //cout << i << ' ' << tr << '\n';
        ans = min(ans,tr);
    }
    cout << ans << '\n';


    return 0;
}
	

