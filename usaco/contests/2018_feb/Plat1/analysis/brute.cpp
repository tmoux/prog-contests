#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int x[maxn], y[maxn], t[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("slingshot.in","r",stdin); freopen("slingshot.out","w",stdout);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> t[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        ll mindist = abs(a-b);
        for (int j = 0; j < n; j++) {
            ll r = 1LL*abs(a-x[j]) + abs(b-y[j]) + t[j];
            mindist = min(mindist,r);
        }
        cout << mindist << '\n';
    }

    return 0;
}

