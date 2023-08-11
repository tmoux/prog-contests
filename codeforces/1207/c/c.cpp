#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, M = 998244353;
int n;
vector<pair<int,int>> a;

ll mult(ll a, ll b) {
    return (1LL*a*b) % M;
}

ll fac[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        a.push_back({u,v});
    }
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mult(fac[i-1],i);
    }
    ll ans = fac[n];
    sort(a.begin(),a.end(),[](auto a, auto b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
            });
    ll f1 = 1;
    int curr = a[0].first;
    int len = 1;
    for (int i = 1; i < n; i++) {
        if (a[i].first != a[i-1].first) {
            f1 = mult(f1,fac[len]);
            curr = a[i].first;
            len = 1;
        }
        else {
            len++;
        }
    }
    f1 = mult(f1,fac[len]);

    ll f3 = 1;
    pair<int,int> cur = a[0];
    len = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i-1]) {
            f3 = mult(f3,fac[len]);
            cur = a[i];
            len = 1;
        }
        else {
            len++;
        }
    }
    f3 = mult(f3,fac[len]);
    //check for inversions
    bool use = true;
    for (int i = 1; i < n; i++) {
        if (a[i].second < a[i-1].second) {
            use = false;
            break;
        }
    }
    if (!use) {
        f3 = 0;
    }

    sort(a.begin(),a.end(),[](auto a, auto b) {
            return a.second < b.second;
            });
    ll f2 = 1;
    curr = a[0].second;
    len = 1;
    for (int i = 1; i < n; i++) {
        if (a[i].second != a[i-1].second) {
            f2 = mult(f2,fac[len]);
            curr = a[i].second;
            len = 1;
        }
        else {
            len++;
        }
    }
    f2 = mult(f2,fac[len]);

    //printf("%d, %d %d %d\n",ans,f1,f2,f3);
    ans = (ans - f1 - f2 + f3 + 5LL*M) % M;
    cout << ans << '\n';
}

