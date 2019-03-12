#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
string s, t;
int n, m;
int nxt[105][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    n = s.size();
    m = t.size();
    memset(nxt,-1,sizeof nxt);
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == t[m-1]) nxt[m-1][i] = i;
        else nxt[m-1][i] = nxt[m-1][i+1];
    }
    for (int i = m - 2; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (s[j] == t[i]) {
                nxt[i][j] = nxt[i+1][j+1];     
            }
            else nxt[i][j] = nxt[i][j+1];
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (nxt[0][i] == -1) continue;
        int left = i + 1, right = n - nxt[0][i];
        //cout << i << ": " << right << '\n';
        ans += right;
    }
    cout << ans << '\n';


    return 0;
}

