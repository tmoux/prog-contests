#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 1; j <= s.size()-i; j++) {
            if (t.find(s.substr(i,j)) != string::npos) {
                //cout << s.substr(i,j) << ' ' << j << '\n';
                ans = max(ans,j);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}

