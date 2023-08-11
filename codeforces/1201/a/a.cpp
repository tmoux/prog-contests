#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s[1005];
int val[1005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> val[i];
    }
    ll total = 0;
    for (int i = 0; i < m; i++) {
        map<char,int> mp;
        for (int j = 0; j < n; j++) {
            mp[s[j][i]]++;
        }
        int mx = 0;
        for (auto p: mp) {
            mx = max(mx,p.second);
        }
        total += val[i]*mx;
    }
    cout << total << '\n';
}

