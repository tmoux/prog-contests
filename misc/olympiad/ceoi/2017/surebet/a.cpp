#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * max(min(Sum_{1 to n} of ai or -1,
 *         Sum_{1 to n} of bi or -1))
 * 
 */

const int maxn = 1e5+5;
int n;
double a[maxn], b[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    sort(a+1,a+1+n,greater<double>());
    sort(b+1,b+1+n,greater<double>());
    for (int i = 1; i <= n; i++) {
        a[i] += a[i-1] - 1;
        b[i] += b[i-1] - 1;
        //cout << a[i] << ' ' << b[i] << '\n';
    }
    double maxans = 0;
    for (int i = 0; i <= n; i++) {
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            int aa = a[i] - mid;
            int bb = b[mid] - i;
            if (bb <= aa) {
                lo = mid+1;
            }
            else {
                hi = mid-1;
            }
        }
        for (int j = max(0,hi-2); j <= min(n,hi+2); j++) {
            maxans = max(maxans,min(a[i]-j,b[j]-i));
        }
    }
    printf("%.4lf\n",(double)maxans);
}

