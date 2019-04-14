#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, t; cin >> n >> t;
    int bestans = 999999;
    int ans = -1;
    for (int i = 0; i < n; i++) {
        int si, di; cin >> si >> di;
        while (si < t) si += di;
        if (si < bestans) {
            bestans = si;
            ans = i+1;
        }
    }
    //cout << bestans << '\n';
    cout << ans << '\n';
}

