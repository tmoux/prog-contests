#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
string s;

int nxt[26][maxn];

int main() {
    cin >> s;
    n = s.size();
    memset(nxt,-1,sizeof nxt);
    for (int k = 25; k >= 0; k--) {
        for (int i = n-1; i >= 0; i--) {
            if (i+1 < n && s[i+1]-'a' == k) {
                nxt[k][i] = i;
            }
            else nxt[k][i] = nxt[k][i+1];
            //cout << k << ' ' << i << ": " << nxt[k][i] << '\n';
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int nx = nxt[s[i]-'a'][i];
        for (int j = 0; j < 26; j++) {
            if (s[i]-'a' == j) continue;
            if (nxt[j][i] != -1 && (nx == -1 || nxt[j][i] < nx)) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
}

