#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 15;
ll dp[maxn];
vector<int> digits;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int d = s.size();
    map<int,int> mp;
    for (char c: s) {
        digits.push_back({c-'0'});
        mp[c-'0']++;
    }

    for (int i = 2; i <= n; i++) {
        map<int,int> newmp;
        for (int j: digits) {
            for (auto& p: mp) {
                newmp[p.first*j] += p.second;                    
            }
        }
        mp = newmp;
        cout << i << ' ' << mp.size() << '\n';
    }

    ll ans = 0;
    for (auto& p: mp) {
        //cout << p.first << ' ' << p.second << '\n';
        ans += 1LL*p.second*p.second;
    }
    cout << ans << '\n';
   

    return 0;
}

