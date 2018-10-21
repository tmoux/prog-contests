#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, k;
const int maxn = 1000006;
ll A[maxn], pre[maxn];

double avg(int l, int r) {
    return (double)(pre[r]-pre[l-1])/(r-l+1);
}

int f(int l, int r) {
    if (l == r) return 1;
    //int ans = max(f(l,(l+r)/2),f((l+r)/2+1,r));        
    int ans = 0;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            if (avg(i,j) <= k) {
                ans = max(ans,j-i+1);
            }
        }
    }
    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    if (n > 10000) return 0;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        pre[i] = pre[i-1] + A[i];
    }
     
    int ans = f(1,n);
    cout << ans << '\n';

    return 0;
}
	

