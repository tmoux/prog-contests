#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 998244353;
const int maxn = 2e5+5;
int nxt[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    ll ans = 0;
    int idx;
    for (int i = n-1; i >= 0; i--) {
        if (i == n - 1) continue;
        if (s[i] != s[i+1]) {
            idx = i+1;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1 || s[i] == s[i-1]) {
            nxt[i] = i;    
        }
        else {
            nxt[i] = nxt[i+1];
        }
    }

    if (s[0] == s[n-1]) {
        int i = -1;
        int idx2 = 0;
        while (s[idx2] == s[0]) idx2++;
        idx2--;
        int x1 = idx2 + 1 + 1;
        int x2 = n - idx + 1;
        ll ans = (1LL*x1*x2) % M;
        cout << ans << '\n';    
    }
    else {
       int idx2 = 0;
       while (s[idx2] == s[0]) idx2++;
       idx2--;
       int x1 = idx2 + 1;
       int x2 = n-idx;
       ll ans = (x1+x2+1) % M;
       cout << ans << '\n';
    }

    return 0;
}

