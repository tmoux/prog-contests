#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
pair<int,int> a[maxn];
int y_pre[maxn], y_suf[maxn];
map<pair<int,int>,int> mp;

int ans[maxn];
int res[maxn];

int main() {
    freopen("codecoder.in","r",stdin); freopen("codecoder.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        mp[a[i]] = i;
    }
    sort(a,a+n);
    y_pre[0] = a[0].second;
    for (int i = 1; i < n; i++) {
        y_pre[i] = max(y_pre[i-1],a[i].second);
    }
    y_suf[n-1] = a[n-1].second;
    for (int i = n-2; i >= 0; i--) {
        y_suf[i] = min(y_suf[i+1],a[i].second);
    }
    int previous = -1;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        if (i > 0) ans[i] = ans[i-1];
        if (i == n-1 || y_pre[i] < y_suf[i+1]) {
            v.push_back(i-previous);

            for (int j = previous+1; j <= i; j++) {
                ans[j] += i-previous;
            }
            previous = i;
        }
    }
    for (int i = 0; i < n; i++) {
        int id = mp[a[i]];
        res[id] = ans[i]-1;
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << '\n';
    }
}
