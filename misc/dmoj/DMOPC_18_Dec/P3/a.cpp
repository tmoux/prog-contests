#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int N, a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];
    int mnA = 999999, aidx, mnB = 999999, bidx;
    int cnt = 0;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += min(a[i],b[i]);
        if (a[i] < b[i]) cnt++;
        if (a[i] < b[i] && b[i] - a[i] < mnA) {
            mnA = b[i] - a[i];
            aidx = i;
        }
        else if (a[i] >= b[i] && a[i] - b[i] < mnB) {
            mnB = a[i] - b[i];
            bidx = i;        
        }
    }
    if ((N-cnt)&1) {
        if (N&1) {
            ans -= b[bidx];
            ans += a[bidx];
        }
        else {
            ans -= a[aidx];
            ans -= b[bidx];
            ans += min(a[aidx]+a[bidx],b[aidx]+b[bidx]);        
        }
    }
    cout << ans << '\n';


    return 0;
}

