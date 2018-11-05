#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 35;
int g[maxn], distr[maxn];
ll pfx[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    k -= n;
    vector<pair<int,int>> vec;
    for (int i = 1; i <= n; i++) {
        int gi; cin >> gi;
        vec.push_back({gi,i});
    }
    sort(vec.begin(),vec.end());
    for (int i = 1; i <= n; i++) {
        pfx[i] = pfx[i-1] + vec[i-1].first;
    }
    if (k % n == 0) {
        cout << 0 << '\n';
        for (int i = 1; i <= n; i++) {
            cout << (k/n+1) << ' ';
        }
        return 0;
    }
    ll mincost = 1e18;
    for (int i = 2; i <= n; i++) {
        int x = n - i + 1;
        if (k % x == 0) {
            ll c = 1LL*pfx[i-1]*x;
            if (c < mincost) {
                mincost = c;
                for (int j = i; j <= n; j++) {
                    distr[j] = k/x;
                }
            }
        }
        else {
            ll c = 1LL*pfx[i-2]*(x+1) + (pfx[i-1]-pfx[i-2])*(x);
            if (c < mincost) {
                mincost = c;
                for (int j = i; j <= n; j++) {
                    distr[j] = k/x;
                }
                distr[i-1] = k%x;
            }
        }
    }

    cout << mincost << '\n';
    vector<int> ans(n+1);
    for (int i = 1; i <= n; i++) {
        ans[vec[i-1].second] = distr[i] + 1;   
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}

