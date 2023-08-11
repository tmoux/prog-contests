#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, x, a[maxn];
int last[maxn], first[maxn];
int first_suf[maxn];

set<int> has;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> x;
    for (int i = 1; i <= x; i++) {
        last[i] = -1;
        first[i] = n+1;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        has.insert(a[i]);
        last[a[i]] = max(last[a[i]],i);
        first[a[i]] = min(first[a[i]],i);
    }
    first_suf[x] = first[x];
    for (int i = x - 1; i >= 1; i--) {
        first_suf[i] = min(first[i],first_suf[i+1]);
    }
    int r = x;
    while (r-1 >= 1 && (last[r-1] < first_suf[r])) r--;
    //cout << r << ": " << last[r-1] << ' ' << first_suf[r] << '\n';
    ll ans = (x+2)-r;
    //cout << "initial = " << ans << '\n';
    int st = 0;
    for (int i = 1; i < x; i++) {
        if (first[i] != n + 1 && first[i] < st) {
            break;
        }
        st = max(st,last[i]);
        while (r <= x && first_suf[r] < st) r++;
        ans += (x+2-r);
        //cout << i << ": " << r << '\n';
    }
    cout << ans << '\n';
}

