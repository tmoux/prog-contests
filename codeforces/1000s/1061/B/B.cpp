#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[100005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int mh = 0;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mh = max(mh,a[i]);
        total += a[i];
    }
    sort(a,a+n,greater<int>());
    ll ans = 0;
    int h = mh;
    for (int i = 0; i < n; i++) {
        if (h == 0) {
            ans++;
            continue;
        }
        else if (h <= a[i+1]) {
            ans++;
            h--;
        }
        else {
            ans += h - a[i+1];
            h = a[i+1];
        }
    }
    cout << (total - ans) << '\n';



    return 0;
}

