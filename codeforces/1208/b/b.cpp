#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        map<int,int> cnt;
        for (int j = 0; j < n; j++) {
            cnt[a[j]]++;
        }
        if (cnt.size() == n) {
            ans = 0;
            break;
        }
        for (int j = i; j < n; j++) {
            if (--cnt[a[j]] == 0) {
                cnt.erase(a[j]);
            }
            if (cnt.size() == n-(j-i+1)) {
                ans = min(ans,j-i+1);
                break;
            }
        }
    }
    cout << ans << '\n';
}

