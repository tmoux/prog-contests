#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
string s, t;
int n, m;
/*
 * let st[i] = be the # of ways get a valid sequence, with strings starting from i
 * answer is st[0] + st[1] + ... + st[n-1]
 * let nxt[i] = be the closest index to i s.t. [i..nxt[i]-1] contains t as a substring
 *  -if nxt[i] == n, then st[i] = 0 (st[n] = 1)
 *  Then st[i] = 1*st[nxt[i]] + 2*st[nxt[i]+1] + 3*st[nxt[i]+1] + ... + x*st[n]
 *  
*/

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

const int maxn = 1e5+5;
int st[maxn], nxt[maxn], suf[maxn];

void madd(int& a, int b) {
    a = (a + b) % M;
}

int main()
{
    cin >> s >> t;
    n = s.size();
    m = t.size();
    vector<int> zs = z_function(t+"#"+s);
    int last = n+1;
    for (int i = n - 1; i >= 0; i--) {
        if (zs[i+m+1] == m) last = i + m;
        nxt[i] = last;
    }
    st[n] = suf[n] = 1;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (nxt[i] != n+1) st[i] = st[nxt[i]];
        //cout << i << ": " << st[i] << '\n';
        madd(suf[i],(suf[i+1]+st[i])%M);
        madd(ans,st[i]);
        madd(st[i],(st[i+1]+suf[i+1])%M);
        //printf("%d: st[%d] = %d, suf[%d] = %d\n",i,i,st[i],i,suf[i]);
    }
    cout << ans << '\n';
    return 0;
}

