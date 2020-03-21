#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5, mx = 29;
int n, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int k = 0; k <= mx; k++) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(a[i] % (1<<(k+1)));
        }
        sort(v.begin(),v.end());
        ll cnt = 0;
        for (auto i: v) {
            int cur = 0;
            auto it = lower_bound(v.begin(),v.end(),(1<<(k+1))-i);
            auto it2 = lower_bound(v.begin(),v.end(),(1<<k)-i);
            cur += distance(it2,it);
            it = lower_bound(v.begin(),v.end(),(1<<(k+1))+(1<<k)-i);
            cur += distance(it,v.end());
            //cout << distance(it,v.end()) << endl;
            if ((i+i)&(1<<k)) {
                --cur;
                //cout << "sub\n";
            }
            cnt += cur;
            //cout << i << ": " << cur << endl;
        }
        cnt /= 2;
        //cout << k << ": " << cnt << endl;
        if (cnt&1) ans |= (1<<k);
    }
    cout << ans << endl;
}
