#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ty[1005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    map<int,int> cnt;
    for (int i = 1; i <= n; i++) {
        cin >> ty[i];
        cnt[ty[i]]++;
    }
    int ans = 0;
    int leftover = 0;
    for (auto p: cnt) {
        ans += (p.second/2)*2;
        if (p.second&1) leftover++;
    }
    ans += (leftover+1)/2;
    cout << ans << '\n';
}

