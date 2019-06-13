#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string sub = s.substr(i,j-i+1);
            map<char,int> mp;
            for (char c: sub) {
                mp[c]++;
            }
            int mn = 9999999;
            int mx = 0;
            for (auto p: mp) {
                mn = min(mn,p.second);
                mx = max(mx,p.second);
                //cout << p.first << ' ' << p.second << '\n';
            }
            //cout << sub << ": " << mn << ' ' << mx << '\n';
            //cout << ans << '\n';
            ans = max(ans,mx-mn);
        }
    }
    cout << ans << '\n';
}

