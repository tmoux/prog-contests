#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
string s;
int diff[maxn], pre[maxn];

int f(string pattern) {
    while (pattern.size() < n) pattern += pattern;
    pattern = '#' + pattern; //for 1-indexed
    //cout << pattern << '\n';
    for (int i = 1; i <= n; i++) {
        if (s[i] != pattern[i]) {
            diff[i] = 1;
        }
        else diff[i] = 0;
        pre[i] = pre[i-1] + diff[i];
        //cout << i << ": " << s[i] << ' ' << pattern[i] << ": " << diff[i] << ' ' << pre[i] << '\n';
    }
    int ans = k;
    for (int i = k; i <= n; i++) {
        ans = min(ans,pre[i]-pre[i-k]);
        //cout << i << ": " << (pre[i]-pre[i-k]) << '\n';
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        cin >> n >> k;
        cin >> s;
        s = '#' + s;
        int ans = f("RGB");            
        ans = min(ans,f("GBR"));
        ans = min(ans,f("BRG"));
        cout << ans << '\n';
    }
}

