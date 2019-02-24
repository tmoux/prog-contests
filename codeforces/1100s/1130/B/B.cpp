#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
vector<int> pos[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(2*n);
    for (int i = 0; i < 2*n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    int curr = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int p1 = pos[i][0];
        ans += abs(curr-p1);
        curr = p1;
        pos[i].erase(pos[i].begin());
    }
    curr = 0;
    for (int i = 1; i <= n; i++) {
       int p1 = pos[i][0];
       ans += abs(curr-p1);
       curr = p1;
    }
    cout << ans << '\n';
}

