#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int ans = 0;
        vector<int> numZeros(s.size());
        for (int i = 0; i < s.size(); i++) {
            if (i > 1 && s[i-1] == '1') numZeros[i] = 1;
            else numZeros[i] = numZeros[i-1] + 1;
        }
        for (int i = 0; i < s.size(); i++) {
            int curr = 0;
            for (int j = i, t = 0; j >= max(0,i-20); j--, t++) {
                if (s[j] == '1') {
                    curr |= (1<<t);
                    if (curr == t+1) ans += numZeros[j];
                }
            }
        }
        cout << ans << '\n';
    }

}

