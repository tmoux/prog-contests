#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<int,int> mp;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            mp[ai]++;
        }
        int c = 2;
        int ans = 0;
        for (int i = 0; i <= 100 && c > 0; i++) {
            if (c == 2) {
                if (mp[i] >= 2) {

                }
                else if (mp[i] == 1) {
                    c--;
                    ans += i;
                }
                else {
                    ans += 2*i;
                    break;
                }
            }
            else if (c == 1) {
                if (mp[i] >= 1) {

                }
                else {
                    ans += i;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}
