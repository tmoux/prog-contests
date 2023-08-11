#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, maxk = 30;
int n, k, a[maxn], pre[maxn];
int invert(int x) {
    return ((1 << k) - 1) ^ x;
}
map<int,int> seen;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    seen[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];            
        int p1 = pre[i-1] ^ a[i];
        int p2 = pre[i-1] ^ invert(a[i]);
        pre[i] = seen[p1] < seen[p2] ? p1 : p2;
        seen[pre[i]]++;
    }
    ll res = 0;
    for (auto& p: seen) {
        ll r = 1LL*p.second * (n + 1 - p.second);
        res += r;
        //cout << p.first << ' ' << p.second << ": " << r << '\n';
    }
    cout << res/2 << '\n';

    return 0;
}

