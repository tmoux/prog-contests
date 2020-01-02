#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn], b[maxn];

ll ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        if (v.empty() || a[i] > v.back().first) {
            v.push_back({a[i],i});
        }
    }
    sort(a,a+n,greater<int>());
    reverse(v.begin(),v.end());
    v.push_back({0,n});
    int pt = 0;
    for (int i = 0; i < v.size()-1; i++) {
        int val = v[i].first;
        int idx = v[i].second;
        while (pt < n && a[pt] > v[i+1].first) {
            while (pt < n && a[pt] >= val) pt++;
            ans[idx+1] += 1LL*pt*(val-a[pt]);
            val = a[pt];
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
