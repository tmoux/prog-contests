#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

map<int,int> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    sort(a,a+n);
    int ans = 0;
    for (int k = 31; k >= 0; k--) {
        for (int i = 0; i < n; i++) {
            if (!mp.count(a[i])) continue;
            int t = (1<<k)-a[i];
            //cout << a[i] << ' ' << t << ' ' << mp.count(t) << endl;
            if (mp.count(t) && (t != a[i] || (t == a[i] && mp[t] > 1))) {
                if (--mp[t] == 0) mp.erase(t);
                if (--mp[a[i]] == 0) mp.erase(a[i]);
                //cout << t << ' ' << a[i] << '\n';
                ans++;
            }
        }
    }
    cout << ans << '\n';
}

