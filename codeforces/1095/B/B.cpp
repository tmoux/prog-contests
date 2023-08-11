#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(),a.end());
    int ans = a.back() - a.front();
    int mx = max(a[1]-a[0],a[n-1]-a[n-2]);
    ans -= mx;
    cout << ans << '\n';

    return 0;
}

