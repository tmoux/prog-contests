#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int k, n, A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    double ans = 0;
    for (int len = k; len <= n; len++) {
        int curr = 0;
        for (int i = 0; i < len; i++) {
            curr += A[i];    
        }
        ans = max(ans,curr/(double)len);
        for (int i = 1; i + len - 1 < n; i++) {
            curr -= A[i-1];
            curr += A[i+len-1];
            ans = max(ans,curr/(double)len);
        }
    }

    cout << fixed << setprecision(10) << ans << '\n';


    return 0;
}
	

