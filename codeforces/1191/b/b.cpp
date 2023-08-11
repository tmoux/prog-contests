#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    map<pair<int,char>,int> mp;
    for (int i = 0; i < 3; i++) {
        int j; char c;
        cin >> j >> c;
        mp[make_pair(j,c)]++;
    }
    int ans = 2;
    vector<char> cs = {'m','p','s'};
    for (int i = 1; i <= 9; i++) {
        for (char c: cs) {
            pair<int,char> p = {i,c};
            if (mp.count(p)) {
                ans = min(ans,3-mp[p]);
            }
        }
    }
    for (int i = 1; i <= 7; i++) {
        for (char c: cs) {
            int need = 3;
            if (mp.count({i,c})) need--;
            if (mp.count({i+1,c})) need--;
            if (mp.count({i+2,c})) need--;
            ans = min(ans,need);
        }
    }
    cout << ans << '\n';
}

