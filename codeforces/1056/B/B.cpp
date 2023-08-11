#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> cnt(m);
    for (int i = 1; i <= m; i++) {
        int num = n/m+(i<=(n%m)?1:0);
        cnt[(i*i)%m] += num;
    }
    for (int i = 0; i < m; i++) {
        //cout << i << ": " << cnt[i] << '\n';
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int d = m-i==m?0:m-i;
        ans += 1LL*cnt[i]*cnt[d];
    }
    cout << ans << '\n';

    return 0;
}

