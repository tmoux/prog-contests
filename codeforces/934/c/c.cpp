#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, a[maxn];
int c1[maxn], c2[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) c1[i]++;
        else c2[i]++;
    }
    for (int i = 1; i <= n+2; i++) {
        c1[i] += c1[i-1];
        c2[i] += c2[i-1];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int st = c1[i-1];
        int mx = 0;
        for (int j = i; j <= n; j++) {
            if (a[j] == 1) mx++;
            else 
                mx = max(mx,c2[j]-c2[i-1]);    

            int en = max(0,c2[n]-c2[j]);
            int tr = st + mx + en;
            ans = max(ans,tr);
        }
    }
    cout << ans << '\n';
}

