#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    pair<int,int> ans = {999999999,-1};
    for (int t = 1; t <= 100; t++) {
        int loss = 0;
        for (int i = 0; i < n; i++) {
            int r = min(abs(a[i]-t),min(abs(a[i]-(t-1)),abs(a[i]-(t+1))));
            loss += r;
        }
        ans = min(ans,{loss,t});
    }
    assert(ans.second != -1);
    cout << ans.second << ' ' << ans.first << '\n';

    return 0;
}

