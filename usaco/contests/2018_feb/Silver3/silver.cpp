#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int,int>> pts;
ll calc(int y) {
    ll r = 0;
    for (auto& p: pts) {
        r += min(abs(p.first-p.second),abs(p.first)+abs(p.second-y));
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("teleport.in","r",stdin); freopen("teleport.out","w",stdout);
    int n; cin >> n;
    int minVal = 1e9, maxVal = -1e9;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        pts.push_back({a,b});
        minVal = min(minVal,min(a,b));
        maxVal = max(maxVal,max(a,b));
    }
    ll lo = minVal, hi = maxVal;
    while (lo < hi) {
        int mid = (lo+hi)>>1;
        //cout << mid << ' ' << calc(mid) << '\n';
        if (calc(mid) < calc(mid+1)) {
            hi = mid;
        }
        else {
            lo = mid+1;
        }
    }
    ll res = 1e18;
    for (int i = lo - 100; i <= lo + 100; i++) {
        res = min(res,calc(i));
    }
    cout << res << '\n';
    

    return 0;
}

