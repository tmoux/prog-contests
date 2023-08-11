#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
vector<int> a;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    a.resize(n+1);
    for (int i = 0; i < n; i++) {
        cin >> a[i+1];
    }
    cin >> q;
    int lastans = 0;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        l = (l + lastans - 1) % n + 1;
        r = (r + lastans - 1) % n + 1;
        if (l > r) swap(l,r);
        if (t == 1) {
            int v = a[r];
            a.erase(a.begin() + r);
            a.insert(a.begin() + l,v);
        }
        else {
            int k; cin >> k;
            k = (k + lastans - 1) % n + 1;
            int ans = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] == k) ans++;  
            }
            cout << ans << '\n';
            lastans = ans;
        }
    }


    return 0;
}

