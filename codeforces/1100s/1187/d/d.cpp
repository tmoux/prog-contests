#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a[maxn], b[maxn];

void solve(map<int,int>& mp) {
    for (auto p: mp) {
        if (p.second != 0) {
            cout << "NO\n";
            return;
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        map<int,int> mp;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mp[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            mp[a[i]]--;
        }
        solve(mp);
    }

}

