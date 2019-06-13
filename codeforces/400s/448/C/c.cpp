#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, a[maxn];

int solve(int l, int r, int h) { //h is the ones already painted
    int mn = 1e9+9;
    for (int i = l; i <= r; i++) {
        mn = min(mn,a[i]);
    }
    int ans = mn-h;
    for (int i = l; i <= r; i++) {
        if (a[i] > mn) {
            int nl = i;
            while (a[i] > mn && i <= n) {
                i++;    
            }
            int nr = i-1;
            ans += solve(nl,nr,mn);    
        }
    }
    ans = min(ans,r-l+1);
    //cerr << l << ' ' << r << ": " << ans << '\n';
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = solve(1,n,0);
    cout << ans << '\n';
}

