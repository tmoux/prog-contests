#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll k;
int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    while (mp.size() > 1) {
        pair<int,int> mn = *mp.begin();
        pair<int,int> mx = *mp.rbegin();
        if (mn.second < mx.second) {
            int d = next(mp.begin())->first - mn.first;
            ll need = 1LL*d*mn.second;
            if (k >= need) {
                k -= need;
                mp.erase(mp.begin());
                mp.begin()->second += mn.second;
            }
            else {
                ll add = k/mn.second;
                mp.erase(mp.begin());
                mp[mn.first+add] = mn.second;
                break;
            }
        }
        else {
            int d = mx.first - next(mp.rbegin())->first;
            ll need = 1LL*d*mx.second;
            //cout << "d = " << d << ", need = " << need << '\n';
            if (k >= need) {
                k -= need;
                mp.erase(prev(mp.end()));
                mp.rbegin()->second += mx.second;
            }
            else {
                ll add = k/mx.second;
                mp.erase(prev(mp.end()));
                mp[mx.first-add] = mx.second;
                break;
            }
        }
        /*
        for (auto p: mp) {
            cout << p.first << ' ' << p.second << '\n';
        }
        cout << "k = " << k << '\n';
        cout << '\n';
        */
    }
    int ans = mp.rbegin()->first - mp.begin()->first;
    cout << ans << '\n';
}

