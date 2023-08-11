#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int alternate(string& s, int pos) {
    char c = s[pos];
    int i = pos + 1, ans = 1;
    while (i < s.size() && s[i] != c) {
        c = s[i];
        ans++;
        i++;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int mx = 0;
    int idx = 0;
    while (idx < s.size()) {
        int tr = alternate(s,idx);
        mx = max(mx,tr);
        idx += tr;
    }
    if (mx == s.size()) {
        cout << mx << '\n';
        return 0;
    }
    int prefix = alternate(s,0);
    reverse(s.begin(),s.end());
    int suffix = alternate(s,0);
    int ans = mx;
    if (s[0] != s[s.size()-1]) {
        ans = max(ans,prefix+suffix);
    }
    cout << ans << '\n';
    
    return 0;
}
	

