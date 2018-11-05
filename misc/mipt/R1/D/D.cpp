#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    sort(a+1,a+m+1);
    multiset<pair<int,int>> q;
    for (int i = 1; i <= m; i++) {
        q.insert({a[i],i});
    }
    ll ans = 0;
    int cnt = 0;
    while (!q.empty()) {
        auto f = *q.begin();
        int w = f.first, i = f.second;
        //cout << w << ' ' << i << '\n';
        ans += w;
        cnt++;
        if (cnt == n) break;
        for (int j = i; j <= m; j++) {
            int nw = w + a[j];
            if (q.size() > m+5000 && nw > ((*q.rbegin()).first)) break;
            q.insert({nw,j});
        }
        q.erase(q.begin());
    }
    cout << ans << '\n';

    return 0;
}

