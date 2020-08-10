#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        int ans = 0;
        for (int i = 0; i < (k+1)/2; i++) {
            map<char,int> mp;
            for (int j = i; j < n; j += k) {
                mp[s[j]]++;
            }
            if (k-1-i != i) {
                for (int j = k-1-i; j < n; j += k) {
                    mp[s[j]]++;
                }
            }
            int mx = 0, sum = 0;
            for (auto p: mp) {
                mx = max(mx,p.second);
                sum += p.second;
            }
            ans += sum-mx;
        }
        cout << ans << '\n';
    }
}

