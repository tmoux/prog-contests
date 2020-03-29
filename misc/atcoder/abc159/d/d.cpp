#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    map<int,int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    ll ans = 0;
    for (auto p: cnt) {
        ans += 1LL*p.second*(p.second-1)/2;
    }
    for (int i = 0; i < n; i++) {
        ans -= 1LL*cnt[a[i]]*(cnt[a[i]]-1)/2;
        cnt[a[i]]--;
        ans += 1LL*cnt[a[i]]*(cnt[a[i]]-1)/2;
        cout << ans << '\n';
        ans -= 1LL*cnt[a[i]]*(cnt[a[i]]-1)/2;
        cnt[a[i]]++;
        ans += 1LL*cnt[a[i]]*(cnt[a[i]]-1)/2;
    }
}

