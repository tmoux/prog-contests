#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> diffs;
    ll total = 0;
    for (int i = 0; i < n - 1; i++) {
        diffs.push_back({a[i+1]-a[i]});
        total += diffs[i];
    }
    sort(diffs.begin(),diffs.end(),greater<int>());
    for (int i = 0; i < k-1; i++) {
        total -= diffs[i];
    }
    cout << total << '\n';
}

