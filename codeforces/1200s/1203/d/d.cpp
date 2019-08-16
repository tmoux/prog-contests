#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s, t;
int n, m;
const int maxn = 2e5+5;
int prematch[maxn], sufmatch[maxn];


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    n = s.size();
    m = t.size();
    int pt = 0;
    for (int i = 0; i < n; i++) {
        if (pt < t.size() && s[i] == t[pt]) {
            pt++;
        }
        prematch[i] = pt; //prematch is length of match
        //cout << i << ": " << prematch[i] << '\n';
    }
    pt = t.size()-1;
    for (int i = n-1; i >= 0; i--) {
        if (pt >= 0 && s[i] == t[pt]) {
            pt--;
        }
        sufmatch[i] = (m-1)-pt;
        //cout << i << ": " << sufmatch[i] << '\n';
    }
    int ans = 0;
    int r = 0;
    for (int i = 0; i < s.size(); i++) {
        while (r < s.size() && prematch[i] + sufmatch[r] >= m) r++;
        //cout << i << ": " << r << '\n';        
        ans = max(ans,r-i-2);
    }
    for (int i = 0; i < s.size(); i++) {
        if (prematch[i] == m) ans = max(ans,(n-1)-i);
    }
    for (int i = 0; i < s.size(); i++) {
        if (sufmatch[i] == m) ans = max(ans,i);
    }
    cout << ans << '\n';
}

