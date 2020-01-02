#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 20;
int n, a[1<<maxn];

void merge(multiset<int>& a, multiset<int> b) {
    for (auto i: b) a.insert(i);
    while (a.size() > 2) a.erase(a.begin());
}

int sum(multiset<int>& a) {
    int res = 0;
    for (int i: a) res += i;
    return res;
}

multiset<int> f[1<<maxn];
int ans[1<<maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < (1<<n); i++) {
        cin >> a[i];
        f[i].insert(a[i]);
    }
    for (int k = 0; k < n; k++) {
        for (int mask = 0; mask < (1<<n); mask++) {
            if (mask & (1<<k)) continue;
            merge(f[mask|1<<k],f[mask]);
        }
    }
    for (int k = 1; k < (1<<n); k++) {
        ans[k] = sum(f[k]);
        ans[k] = max(ans[k],ans[k-1]);
        cout << ans[k] << '\n';
    }
}

