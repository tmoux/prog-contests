#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pair<int,int>> ps(n);
    for (int i = 0; i < n; i++) {
        cin >> ps[i].first >> ps[i].second;
    }
    int k; cin >> k;
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += ps[i].second - ps[i].first + 1;
        if (total >= k) {
            cout << (n-i) << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
}

