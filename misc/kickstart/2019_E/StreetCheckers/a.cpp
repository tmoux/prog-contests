#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int,int> mp;
void factor(int i) {
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                mp[j]++;
                i /= j;
            }
            factor(i);
            return;
        }
    }
    if (i > 1) mp[i]++;
}

int diff(int i) {
    mp.clear();
    factor(i);
    int cnt = 1;
    int twoCount = 0;
    //cout << i << ":\n";
    for (auto& p: mp) {
        //cout << p.first << ' ' << p.second << '\n';
        if (p.first == 2) twoCount = p.second;
        else cnt *= p.second+1;
    }
    //cout << cnt << '\n';
    int d = abs(twoCount*cnt - cnt);
    //cout << d << '\n';
    return d;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        int L, R; cin >> L >> R;
        int ans = 0;
        for (int i = L; i <= R; i++) {
            //cout << i << ": " << diff(i) << '\n';
            if (diff(i) <= 2) ans++;
        }
        cout << ans << '\n';
    }
}
