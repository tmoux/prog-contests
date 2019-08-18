#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int ans = 0;
    string pre = "";
    for (int i = 0; i < s.size(); i++) {
        string r;
        r += s[i];
        if (r != pre) {
            ans++;
            pre = s[i];
        }
        else {
            if (i+1 == s.size()) {
                break;
            }
            else {
                ans++;
                pre = s[i] + s[i+1];
                i++;
            }
        }
    }
    cout << ans << '\n';
}
