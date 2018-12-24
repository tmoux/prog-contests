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
    int ans = 0;
    for (int i = 0; i < n; i += 2) {
        ans += (a[i+1] - a[i]);
    }
    cout << ans << '\n';

    return 0;
}

